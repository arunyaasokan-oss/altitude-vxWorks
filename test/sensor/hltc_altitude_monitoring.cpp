#include <gtest/gtest.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <pthread.h>

extern "C" {
    #include "../../source/sensor/sensor.h"
    #include "../../source/sensor/altitudemeasure.h"
    #include "../../source/sensor/alarm.h"
    #include "mock_sensor.h"
    uint32_t sensorReadData(uint32_t ulAltitudeValue);
}

static bool should_mq_send_fail = false;
int mock_pthread_return_value = 0; 

extern "C" int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio) {
    if (should_mq_send_fail) {
        return -1; 
    }
    return 0; 
}
static bool should_mq_open_fail = false;
extern "C" {
    // Correct variadic signature to match /usr/include/mqueue.h
    mqd_t mq_open(const char *name, int oflag, ...) {
        if (should_mq_open_fail) {
            errno = EACCES;
            return (mqd_t)-1;
        }
        va_list ap;
        va_start(ap, oflag);
        // If O_CREAT is set, mq_open expects 2 more args
        if (oflag & O_CREAT) {
            mode_t mode = va_arg(ap, mode_t);
            struct mq_attr *attr = va_arg(ap, struct mq_attr *);
            (void)mode; (void)attr; // suppress unused warning
        }
        va_end(ap);

        return (mqd_t)42;  // Return our mock descriptor
    }
}

static uint32_t mock_received_altitude = 0;

extern "C" {
    ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio) 
    {
       memcpy(msg_ptr, &mock_received_altitude, sizeof(uint32_t));
       return (ssize_t)sizeof(uint32_t);
    }
    int pthread_mutex_lock(pthread_mutex_t *mutex) { return 0; }
    int pthread_mutex_unlock(pthread_mutex_t *mutex) { return 0; }
    int pthread_cond_signal(pthread_cond_t *cond) { return 0; }  
}
extern "C" {
    int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
        ulAlarmReady = 1; 
        return 0; 
    }
}

extern "C" {
    // Your Mock Function
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                       void *(*start_routine) (void *), void *arg) {
        return mock_pthread_return_value; // Returns 0 or 11 (EAGAIN)
    }
}


// Test case 1: LLR2 - Frequency greater than zero
TEST(sensorInitialization_HLTC_1, sensorIntialization_validFrequency_Test)
{
    EXPECT_TRUE(sensorIntialization(10000));
}

// Test case 2: LLR1- Frequency is 0 or negative (should return FALSE)
TEST(sensorInitialization_HLTC_2, sensorIntialization_InvalidFrequency_Test)
{
    EXPECT_FALSE(sensorIntialization(0));
    EXPECT_FALSE(sensorIntialization(-100));
}

TEST(sensorAltitudeInit_HLTC_2, sensorAltitudeInit_task_Create_Failure) 
{
    mock_pthread_return_value = 11; 
    uint8_t st = sensorAltitudeInit();
    EXPECT_EQ(st, SENSOR_STATE_ERROR);
    mock_pthread_return_value = 0;
}

TEST(sensorAltitudeInit_HLTC_1, sensorAltitudeInit_task_Create_Success) {
    mock_pthread_return_value = 0; // Ensure success
    uint8_t st = sensorAltitudeInit();
    EXPECT_EQ(st, SENSOR_STATE_SUCCESS);
}

TEST(sensorReadHandler_LLTC_2, TestMqOpenFailureReturnsNull) {
    // 1. Setup: Tell the mock to fail
    should_mq_open_fail = true;
    void* result = sensorReadHandler(NULL);
    EXPECT_EQ(result, nullptr);
    should_mq_open_fail = false;
}

TEST(sensorReadData_LLTC_1,TestOverflowCoverage)
{
   uint32_t ulValue = mock_HighValue();

   uint32_t result = sensorReadData(ulValue);
   EXPECT_EQ(result, 0);
}
TEST(sensorReadData_LLTC_2,TestUnderflowCoverage)
{
   uint32_t ulValue = mock_LowValue();

   uint32_t result = sensorReadData(ulValue);
   EXPECT_EQ(result, 0);
}

TEST(sensorReadData_LLTC_3,TestValidRangeCoverage)
{
   uint32_t ulValue = mock_ValidValue();

   uint32_t result = sensorReadData(ulValue);
   EXPECT_EQ(result, 5000);
}

TEST(sensorReadHandlerHLTC_2, TestSendFaileCoverage) 
{
    should_mq_send_fail = true; 
    sensorReadHandler(NULL); 
    should_mq_send_fail = false;
}
TEST(sensorReadHandlerHLTC_3, TestSendSuccessCoverage) 
{
    should_mq_send_fail = false; 
    sensorReadHandler(NULL); 
}

TEST(processSensorData_HLTC_1, ProcessWithoutAlarm) 
{
    mock_received_altitude = 1000; 
    processSensorData(NULL);
}

TEST(processSensorData_HLTC_2, ProcessWithAlarm) 
{
    mock_received_altitude = 30000; 
    processSensorData(NULL);
}
TEST(alarmProcessHandler_LLTC_1, TestAlarmReadyAsOne) 
{
    ulAlarmReady = 0; 
    alarmProcessHandler(NULL); 
}



int main(int argc, char **argv) 
{ 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}

