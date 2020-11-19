/**
 * Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "stdint.h"
#include "stddef.h"

#include "system_config.h"


/* Exported types/defines/enums ----------------------------------------------*/
typedef struct
{
    const char* parameterName[NUM_TEST_PARAMETERS];
    size_t parameterSize[NUM_TEST_PARAMETERS];
    size_t newParameterSize[NUM_TEST_PARAMETERS];
    union
    {
        uint32_t    uint32Value[NUM_TEST_PARAMETERS];
        uint64_t    uint64Value[NUM_TEST_PARAMETERS];
        const char* stringValue[NUM_TEST_PARAMETERS];
        const void* rawValue[NUM_TEST_PARAMETERS];
    } parameterValue;
    union
    {
        uint32_t    uint32Value[NUM_TEST_PARAMETERS];
        uint64_t    uint64Value[NUM_TEST_PARAMETERS];
        const char* stringValue[NUM_TEST_PARAMETERS];
        const void* rawValue[NUM_TEST_PARAMETERS];
    } newParameterValue;
} TestData_t;

typedef struct
{
    const char* appDomainName;
    const char* appComponentName;
    TestData_t  uint32TestData;
    TestData_t  uint64TestData;
    TestData_t  strTestData;
    TestData_t  blobTestData;
} TestApp_t;