/**
 * Copyright (C) 2019, Hensoldt Cyber GmbH
 *
 * OS libraries configurations
 */

#pragma once

//-----------------------------------------------------------------------------
// Debug
//-----------------------------------------------------------------------------
#if !defined(NDEBUG)
#define Debug_Config_STANDARD_ASSERT
#define Debug_Config_ASSERT_SELF_PTR
#else
#define Debug_Config_DISABLE_ASSERT
#define Debug_Config_NO_ASSERT_SELF_PTR
#endif

#define Debug_Config_LOG_LEVEL Debug_LOG_LEVEL_INFO
#define Debug_Config_INCLUDE_LEVEL_IN_MSG
#define Debug_Config_LOG_WITH_FILE_LINE

//-----------------------------------------------------------------------------
// Memory
//-----------------------------------------------------------------------------
#define Memory_Config_USE_STDLIB_ALLOC

//-----------------------------------------------------------------------------
// RamDisk
//-----------------------------------------------------------------------------
// arbitrary size that should be able to hold the config parameters
#define RAMDISK_SIZE_BYTES (1024*1024)


#define CREATE_FS_BACKEND //Can be set to create the ConfigFile by the ConfigFileInjector on system startup

//App1
#define TEST_APP1   "TestApp1"
#define DOMAIN_APP1 "Domain_App1"

#define APP1_PARAMETER_32_NAME_0       "App1_Parameter_32_0"
#define APP1_PARAMETER_32_VALUE_0      0x41
#define APP1_PARAMETER_32_VALUE_0_NEW  0x7CF321

#define APP1_PARAMETER_32_NAME_1       "App1_Parameter_32_1"
#define APP1_PARAMETER_32_VALUE_1      0x100001
#define APP1_PARAMETER_32_VALUE_1_NEW  0x6215E1

#define APP1_PARAMETER_32_NAME_2       "App1_Parameter_32_2"
#define APP1_PARAMETER_32_VALUE_2      0x80000001
#define APP1_PARAMETER_32_VALUE_2_NEW  0x217721

#define APP1_PARAMETER_32_NAME_3       "App1_Parameter_32_3"
#define APP1_PARAMETER_32_VALUE_3      0xFFFFFFF1
#define APP1_PARAMETER_32_VALUE_3_NEW  0x1A24E1


#define APP1_PARAMETER_64_NAME_0       "App1_Parameter_64_0"
#define APP1_PARAMETER_64_VALUE_0      0x20001
#define APP1_PARAMETER_64_VALUE_0_NEW  0x3CB6C1

#define APP1_PARAMETER_64_NAME_1       "App1_Parameter_64_1"
#define APP1_PARAMETER_64_VALUE_1      0x106CF3B641
#define APP1_PARAMETER_64_VALUE_1_NEW  0x781F1

#define APP1_PARAMETER_64_NAME_2       "App1_Parameter_64_2"
#define APP1_PARAMETER_64_VALUE_2      0x2000000001
#define APP1_PARAMETER_64_VALUE_2_NEW  0x368671

#define APP1_PARAMETER_64_NAME_3       "App1_Parameter_64_3"
#define APP1_PARAMETER_64_VALUE_3      0xAABBCCDD00112231
#define APP1_PARAMETER_64_VALUE_3_NEW  0x128811


#define APP1_PARAMETER_STRING_NAME_0      "App1_Parameter_String_0"
#define APP1_PARAMETER_STRING_VALUE_0     "App1_Hello_World!_0"
#define APP1_PARAMETER_STRING_VALUE_0_NEW "App1_Hello_World!_0_NEW"

#define APP1_PARAMETER_STRING_NAME_1      "App1_Parameter_String_1"
#define APP1_PARAMETER_STRING_VALUE_1     "App1_Hello_World!_1"
#define APP1_PARAMETER_STRING_VALUE_1_NEW "App1_Hello_World!_1_NEW"

#define APP1_PARAMETER_STRING_NAME_2      "App1_Parameter_String_2"
#define APP1_PARAMETER_STRING_VALUE_2     "App1_Hello_World!_2"
#define APP1_PARAMETER_STRING_VALUE_2_NEW "App1_Hello_World!_2_NEW"

#define APP1_PARAMETER_STRING_NAME_3      "App1_Parameter_String_3"
#define APP1_PARAMETER_STRING_VALUE_3     "App1_Hello_World!_3"
#define APP1_PARAMETER_STRING_VALUE_3_NEW "App1_Hello_World!_3_NEW"


#define APP1_PARAMETER_BLOB_NAME_0        "App1_Parameter_Blob_0"
#define APP1_PARAMETER_BLOB_VALUE_0       "App1_Blob: Hello World!_0"
#define APP1_PARAMETER_BLOB_VALUE_0_NEW   "App1_Blob: Hello World!_0_NEW"

#define APP1_PARAMETER_BLOB_NAME_1        "App1_Parameter_Blob_1"
#define APP1_PARAMETER_BLOB_VALUE_1       "App1_Blob: Hello World!_1"
#define APP1_PARAMETER_BLOB_VALUE_1_NEW   "App1_Blob: Hello World!_1_NEW"

#define APP1_PARAMETER_BLOB_NAME_2        "App1_Parameter_Blob_2"
#define APP1_PARAMETER_BLOB_VALUE_2       "App1_Blob: Hello World!_2"
#define APP1_PARAMETER_BLOB_VALUE_2_NEW   "App1_Blob: Hello World!_2_NEW"

#define APP1_PARAMETER_BLOB_NAME_3    "App1_Parameter_Blob_3"
#define APP1_PARAMETER_BLOB_VALUE_3                                           \
    "-----BEGIN CERTIFICATE-----\r\n"                                     \
    "MIIFtDCCBJygAwIBAgIQC2qzsD6xqfbEYJJqqM3+szANBgkqhkiG9w0BAQsFADBa\r\n" \
    "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n" \
    "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTE2\r\n" \
    "MDUyMDEyNTIzOFoXDTI0MDUyMDEyNTIzOFowgYsxCzAJBgNVBAYTAlVTMRMwEQYD\r\n" \
    "VQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNy\r\n" \
    "b3NvZnQgQ29ycG9yYXRpb24xFTATBgNVBAsTDE1pY3Jvc29mdCBJVDEeMBwGA1UE\r\n" \
    "AxMVTWljcm9zb2Z0IElUIFRMUyBDQSA0MIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\r\n" \
    "MIICCgKCAgEAq+XrXaNrOZ71NIgSux1SJl19CQvGeY6rtw7fGbLd7g/27vRW5Ebi\r\n" \
    "kg/iZwvjHHGk1EFztMuZFo6/d32wrx5s7XEuwwh3Sl6Sruxa0EiB0MXpoPV6jx6N\r\n" \
    "XtOtksDaxpE1MSC5OQTNECo8lx0AnpkYGAnPS5fkyfwA8AxanTboskDBSqyEKKo9\r\n" \
    "Rhgrp4qs9K9LqH5JQsdiIMDmpztd65Afu4rYnJDjOrFswpTOPjJry3GzQS65xeFd\r\n" \
    "2FkngvvhSA1+6ATx+QEnQfqUWn3FMLu2utcRm4j6AcxuS5K5+Hg8y5xomhZmiNCT\r\n" \
    "sCqDLpcRHX6BIGHksLmbnG5TlZUixtm9dRC62XWMPD8d0Jb4M0V7ex9UM+VIl6cF\r\n" \
    "JKLb0dyVriAqfZaJSHuSetAksd5IEfdnPLTf+Fhg9U97NGjm/awmCLbzLEPbT8QW\r\n" \
    "0JsMcYexB2uG3Y+gsftm2tjL6fLwZeWO2BzqL7otZPFe0BtQsgyFSs87yC4qanWM\r\n" \
    "wK5c2enAfH182pzjvUqwYAeCK31dyBCvLmKM3Jr94dm5WUiXQhrDUIELH4Mia+Sb\r\n" \
    "vCkigv2AUVx1Xw41wt1/L3pnnz2OW4y7r530zAz7qB+dIcHz51IaXc4UV21QuEnu\r\n" \
    "sQsn0uJpJxJuxsAmPuekKxuLUzgG+hqHOuBLf5kWTlk9WWnxcadlZRsCAwEAAaOC\r\n" \
    "AUIwggE+MB0GA1UdDgQWBBR6e4zBz+egyhzUa/r74TPDDxqinTAfBgNVHSMEGDAW\r\n" \
    "gBTlnVkwgkdYzKz6CFQ2hns6tQRN8DASBgNVHRMBAf8ECDAGAQH/AgEAMA4GA1Ud\r\n" \
    "DwEB/wQEAwIBhjAnBgNVHSUEIDAeBggrBgEFBQcDAQYIKwYBBQUHAwIGCCsGAQUF\r\n" \
    "BwMJMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGln\r\n" \
    "aWNlcnQuY29tMDoGA1UdHwQzMDEwL6AtoCuGKWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0\r\n" \
    "LmNvbS9PbW5pcm9vdDIwMjUuY3JsMD0GA1UdIAQ2MDQwMgYEVR0gADAqMCgGCCsG\r\n" \
    "AQUFBwIBFhxodHRwczovL3d3dy5kaWdpY2VydC5jb20vQ1BTMA0GCSqGSIb3DQEB\r\n" \
    "CwUAA4IBAQAR/nIGOiEKN27I9SkiAmKeRQ7t+gaf77+eJDUX/jmIsrsB4Xjf0YuX\r\n" \
    "/bd38YpyT0k66LMp13SH5LnzF2CHiJJVgr3ZfRNIfwaQOolm552W95XNYA/X4cr2\r\n" \
    "du76mzVIoZh90pMqT4EWx6iWu9El86ZvUNoAmyqo9DUA4/0sO+3lFZt/Fg/Hjsk2\r\n" \
    "IJTwHQG5ElBQmYHgKEIsjnj/7cae1eTK6aCqs0hPpF/kixj/EwItkBE2GGYoOiKa\r\n" \
    "3pXxWe6fbSoXdZNQwwUS1d5ktLa829d2Wf6l1uVW4f5GXDuK+OwO++8SkJHOIBKB\r\n" \
    "ujxS43/jQPQMQSBmhxjaMmng9tyPKPK1\r\n"                                 \
    "-----END CERTIFICATE-----\r\n"

#define APP1_PARAMETER_BLOB_VALUE_3_NEW   "App1_Blob: Hello World!_3_NEW"

//App2
#define TEST_APP2   "TestApp2"
#define DOMAIN_APP2 "Domain_App2"

#define APP2_PARAMETER_32_NAME_0       "App2_Parameter_32_0"
#define APP2_PARAMETER_32_VALUE_0      0x42
#define APP2_PARAMETER_32_VALUE_0_NEW  0x7CF322

#define APP2_PARAMETER_32_NAME_1       "App2_Parameter_32_1"
#define APP2_PARAMETER_32_VALUE_1      0x100002
#define APP2_PARAMETER_32_VALUE_1_NEW  0x6215E2

#define APP2_PARAMETER_32_NAME_2       "App2_Parameter_32_2"
#define APP2_PARAMETER_32_VALUE_2      0x80000002
#define APP2_PARAMETER_32_VALUE_2_NEW  0x217722

#define APP2_PARAMETER_32_NAME_3       "App2_Parameter_32_3"
#define APP2_PARAMETER_32_VALUE_3      0xFFFFFFF2
#define APP2_PARAMETER_32_VALUE_3_NEW  0x1A24E2


#define APP2_PARAMETER_64_NAME_0       "App2_Parameter_64_0"
#define APP2_PARAMETER_64_VALUE_0      0x20002
#define APP2_PARAMETER_64_VALUE_0_NEW  0x3CB6C2

#define APP2_PARAMETER_64_NAME_1       "App2_Parameter_64_1"
#define APP2_PARAMETER_64_VALUE_1      0x106CF3B642
#define APP2_PARAMETER_64_VALUE_1_NEW  0x781F2

#define APP2_PARAMETER_64_NAME_2       "App2_Parameter_64_2"
#define APP2_PARAMETER_64_VALUE_2      0x2000000002
#define APP2_PARAMETER_64_VALUE_2_NEW  0x368672

#define APP2_PARAMETER_64_NAME_3       "App2_Parameter_64_3"
#define APP2_PARAMETER_64_VALUE_3      0xAABBCCDD00112232
#define APP2_PARAMETER_64_VALUE_3_NEW  0x128812


#define APP2_PARAMETER_STRING_NAME_0      "App2_Parameter_String_0"
#define APP2_PARAMETER_STRING_VALUE_0     "App2_Hello_World!_0"
#define APP2_PARAMETER_STRING_VALUE_0_NEW "App2_Hello_World!_0_NEW"

#define APP2_PARAMETER_STRING_NAME_1      "App2_Parameter_String_1"
#define APP2_PARAMETER_STRING_VALUE_1     "App2_Hello_World!_1"
#define APP2_PARAMETER_STRING_VALUE_1_NEW "App2_Hello_World!_1_NEW"

#define APP2_PARAMETER_STRING_NAME_2      "App2_Parameter_String_2"
#define APP2_PARAMETER_STRING_VALUE_2     "App2_Hello_World!_2"
#define APP2_PARAMETER_STRING_VALUE_2_NEW "App2_Hello_World!_2_NEW"

#define APP2_PARAMETER_STRING_NAME_3      "App2_Parameter_String_3"
#define APP2_PARAMETER_STRING_VALUE_3     "App2_Hello_World!_3"
#define APP2_PARAMETER_STRING_VALUE_3_NEW "App2_Hello_World!_3_NEW"


#define APP2_PARAMETER_BLOB_NAME_0        "App2_Parameter_Blob_0"
#define APP2_PARAMETER_BLOB_VALUE_0       "App2_Blob: Hello World!_0"
#define APP2_PARAMETER_BLOB_VALUE_0_NEW   "App2_Blob: Hello World!_0_NEW"

#define APP2_PARAMETER_BLOB_NAME_1        "App2_Parameter_Blob_1"
#define APP2_PARAMETER_BLOB_VALUE_1       "App2_Blob: Hello World!_1"
#define APP2_PARAMETER_BLOB_VALUE_1_NEW   "App2_Blob: Hello World!_1_NEW"

#define APP2_PARAMETER_BLOB_NAME_2        "App2_Parameter_Blob_2"
#define APP2_PARAMETER_BLOB_VALUE_2       "App2_Blob: Hello World!_2"
#define APP2_PARAMETER_BLOB_VALUE_2_NEW   "App2_Blob: Hello World!_2_NEW"

#define APP2_PARAMETER_BLOB_NAME_3    "App2_Parameter_Blob_3"
#define APP2_PARAMETER_BLOB_VALUE_3                                           \
    "-----BEGIN CERTIFICATE-----\r\n"                                     \
    "MIIFtDCCBJygAwIBAgIQC2qzsD6xqfbEYJJqqM3+szANBgkqhkiG9w0BAQsFADBa\r\n" \
    "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n" \
    "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTE2\r\n" \
    "MDUyMDEyNTIzOFoXDTI0MDUyMDEyNTIzOFowgYsxCzAJBgNVBAYTAlVTMRMwEQYD\r\n" \
    "VQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNy\r\n" \
    "b3NvZnQgQ29ycG9yYXRpb24xFTATBgNVBAsTDE1pY3Jvc29mdCBJVDEeMBwGA1UE\r\n" \
    "AxMVTWljcm9zb2Z0IElUIFRMUyBDQSA0MIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\r\n" \
    "MIICCgKCAgEAq+XrXaNrOZ71NIgSux1SJl19CQvGeY6rtw7fGbLd7g/27vRW5Ebi\r\n" \
    "kg/iZwvjHHGk1EFztMuZFo6/d32wrx5s7XEuwwh3Sl6Sruxa0EiB0MXpoPV6jx6N\r\n" \
    "XtOtksDaxpE1MSC5OQTNECo8lx0AnpkYGAnPS5fkyfwA8AxanTboskDBSqyEKKo9\r\n" \
    "Rhgrp4qs9K9LqH5JQsdiIMDmpztd65Afu4rYnJDjOrFswpTOPjJry3GzQS65xeFd\r\n" \
    "2FkngvvhSA1+6ATx+QEnQfqUWn3FMLu2utcRm4j6AcxuS5K5+Hg8y5xomhZmiNCT\r\n" \
    "sCqDLpcRHX6BIGHksLmbnG5TlZUixtm9dRC62XWMPD8d0Jb4M0V7ex9UM+VIl6cF\r\n" \
    "JKLb0dyVriAqfZaJSHuSetAksd5IEfdnPLTf+Fhg9U97NGjm/awmCLbzLEPbT8QW\r\n" \
    "0JsMcYexB2uG3Y+gsftm2tjL6fLwZeWO2BzqL7otZPFe0BtQsgyFSs87yC4qanWM\r\n" \
    "wK5c2enAfH182pzjvUqwYAeCK31dyBCvLmKM3Jr94dm5WUiXQhrDUIELH4Mia+Sb\r\n" \
    "vCkigv2AUVx1Xw41wt1/L3pnnz2OW4y7r530zAz7qB+dIcHz51IaXc4UV21QuEnu\r\n" \
    "sQsn0uJpJxJuxsAmPuekKxuLUzgG+hqHOuBLf5kWTlk9WWnxcadlZRsCAwEAAaOC\r\n" \
    "AUIwggE+MB0GA1UdDgQWBBR6e4zBz+egyhzUa/r74TPDDxqinTAfBgNVHSMEGDAW\r\n" \
    "gBTlnVkwgkdYzKz6CFQ2hns6tQRN8DASBgNVHRMBAf8ECDAGAQH/AgEAMA4GA1Ud\r\n" \
    "DwEB/wQEAwIBhjAnBgNVHSUEIDAeBggrBgEFBQcDAQYIKwYBBQUHAwIGCCsGAQUF\r\n" \
    "BwMJMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGln\r\n" \
    "aWNlcnQuY29tMDoGA1UdHwQzMDEwL6AtoCuGKWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0\r\n" \
    "LmNvbS9PbW5pcm9vdDIwMjUuY3JsMD0GA1UdIAQ2MDQwMgYEVR0gADAqMCgGCCsG\r\n" \
    "AQUFBwIBFhxodHRwczovL3d3dy5kaWdpY2VydC5jb20vQ1BTMA0GCSqGSIb3DQEB\r\n" \
    "CwUAA4IBAQAR/nIGOiEKN27I9SkiAmKeRQ7t+gaf77+eJDUX/jmIsrsB4Xjf0YuX\r\n" \
    "/bd38YpyT0k66LMp13SH5LnzF2CHiJJVgr3ZfRNIfwaQOolm552W95XNYA/X4cr2\r\n" \
    "du76mzVIoZh90pMqT4EWx6iWu9El86ZvUNoAmyqo9DUA4/0sO+3lFZt/Fg/Hjsk2\r\n" \
    "IJTwHQG5ElBQmYHgKEIsjnj/7cae1eTK6aCqs0hPpF/kixj/EwItkBE2GGYoOiKa\r\n" \
    "3pXxWe6fbSoXdZNQwwUS1d5ktLa829d2Wf6l1uVW4f5GXDuK+OwO++8SkJHOIBKB\r\n" \
    "ujxS43/jQPQMQSBmhxjaMmng9tyPKPK2\r\n"                                 \
    "-----END CERTIFICATE-----\r\n"

#define APP2_PARAMETER_BLOB_VALUE_3_NEW   "App2_Blob: Hello World!_3_NEW"

//App3
#define TEST_APP3   "TestApp3"
#define DOMAIN_APP3 "Domain_App3"

#define APP3_PARAMETER_32_NAME_0       "App3_Parameter_32_0"
#define APP3_PARAMETER_32_VALUE_0      0x43
#define APP3_PARAMETER_32_VALUE_0_NEW  0x7CF323

#define APP3_PARAMETER_32_NAME_1       "App3_Parameter_32_1"
#define APP3_PARAMETER_32_VALUE_1      0x100003
#define APP3_PARAMETER_32_VALUE_1_NEW  0x6215E3

#define APP3_PARAMETER_32_NAME_2       "App3_Parameter_32_2"
#define APP3_PARAMETER_32_VALUE_2      0x80000003
#define APP3_PARAMETER_32_VALUE_2_NEW  0x217723

#define APP3_PARAMETER_32_NAME_3       "App3_Parameter_32_3"
#define APP3_PARAMETER_32_VALUE_3      0xFFFFFFF3
#define APP3_PARAMETER_32_VALUE_3_NEW  0x1A24E3


#define APP3_PARAMETER_64_NAME_0       "App3_Parameter_64_0"
#define APP3_PARAMETER_64_VALUE_0      0x20003
#define APP3_PARAMETER_64_VALUE_0_NEW  0x3CB6C3

#define APP3_PARAMETER_64_NAME_1       "App3_Parameter_64_1"
#define APP3_PARAMETER_64_VALUE_1      0x106CF3B643
#define APP3_PARAMETER_64_VALUE_1_NEW  0x781F3

#define APP3_PARAMETER_64_NAME_2       "App3_Parameter_64_2"
#define APP3_PARAMETER_64_VALUE_2      0x2000000003
#define APP3_PARAMETER_64_VALUE_2_NEW  0x368673

#define APP3_PARAMETER_64_NAME_3       "App3_Parameter_64_3"
#define APP3_PARAMETER_64_VALUE_3      0xAABBCCDD00112233
#define APP3_PARAMETER_64_VALUE_3_NEW  0x128813


#define APP3_PARAMETER_STRING_NAME_0      "App3_Parameter_String_0"
#define APP3_PARAMETER_STRING_VALUE_0     "App3_Hello_World!_0"
#define APP3_PARAMETER_STRING_VALUE_0_NEW "App3_Hello_World!_0_NEW"

#define APP3_PARAMETER_STRING_NAME_1      "App3_Parameter_String_1"
#define APP3_PARAMETER_STRING_VALUE_1     "App3_Hello_World!_1"
#define APP3_PARAMETER_STRING_VALUE_1_NEW "App3_Hello_World!_1_NEW"

#define APP3_PARAMETER_STRING_NAME_2      "App3_Parameter_String_2"
#define APP3_PARAMETER_STRING_VALUE_2     "App3_Hello_World!_2"
#define APP3_PARAMETER_STRING_VALUE_2_NEW "App3_Hello_World!_2_NEW"

#define APP3_PARAMETER_STRING_NAME_3      "App3_Parameter_String_3"
#define APP3_PARAMETER_STRING_VALUE_3     "App3_Hello_World!_3"
#define APP3_PARAMETER_STRING_VALUE_3_NEW "App3_Hello_World!_3_NEW"


#define APP3_PARAMETER_BLOB_NAME_0        "App3_Parameter_Blob_0"
#define APP3_PARAMETER_BLOB_VALUE_0       "App3_Blob: Hello World!_0"
#define APP3_PARAMETER_BLOB_VALUE_0_NEW   "App3_Blob: Hello World!_0_NEW"

#define APP3_PARAMETER_BLOB_NAME_1        "App3_Parameter_Blob_1"
#define APP3_PARAMETER_BLOB_VALUE_1       "App3_Blob: Hello World!_1"
#define APP3_PARAMETER_BLOB_VALUE_1_NEW   "App3_Blob: Hello World!_1_NEW"

#define APP3_PARAMETER_BLOB_NAME_2        "App3_Parameter_Blob_2"
#define APP3_PARAMETER_BLOB_VALUE_2       "App3_Blob: Hello World!_2"
#define APP3_PARAMETER_BLOB_VALUE_2_NEW   "App3_Blob: Hello World!_2_NEW"

#define APP3_PARAMETER_BLOB_NAME_3    "App3_Parameter_Blob_3"
#define APP3_PARAMETER_BLOB_VALUE_3                                           \
    "-----BEGIN CERTIFICATE-----\r\n"                                     \
    "MIIFtDCCBJygAwIBAgIQC2qzsD6xqfbEYJJqqM3+szANBgkqhkiG9w0BAQsFADBa\r\n" \
    "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n" \
    "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTE2\r\n" \
    "MDUyMDEyNTIzOFoXDTI0MDUyMDEyNTIzOFowgYsxCzAJBgNVBAYTAlVTMRMwEQYD\r\n" \
    "VQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNy\r\n" \
    "b3NvZnQgQ29ycG9yYXRpb24xFTATBgNVBAsTDE1pY3Jvc29mdCBJVDEeMBwGA1UE\r\n" \
    "AxMVTWljcm9zb2Z0IElUIFRMUyBDQSA0MIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\r\n" \
    "MIICCgKCAgEAq+XrXaNrOZ71NIgSux1SJl19CQvGeY6rtw7fGbLd7g/27vRW5Ebi\r\n" \
    "kg/iZwvjHHGk1EFztMuZFo6/d32wrx5s7XEuwwh3Sl6Sruxa0EiB0MXpoPV6jx6N\r\n" \
    "XtOtksDaxpE1MSC5OQTNECo8lx0AnpkYGAnPS5fkyfwA8AxanTboskDBSqyEKKo9\r\n" \
    "Rhgrp4qs9K9LqH5JQsdiIMDmpztd65Afu4rYnJDjOrFswpTOPjJry3GzQS65xeFd\r\n" \
    "2FkngvvhSA1+6ATx+QEnQfqUWn3FMLu2utcRm4j6AcxuS5K5+Hg8y5xomhZmiNCT\r\n" \
    "sCqDLpcRHX6BIGHksLmbnG5TlZUixtm9dRC62XWMPD8d0Jb4M0V7ex9UM+VIl6cF\r\n" \
    "JKLb0dyVriAqfZaJSHuSetAksd5IEfdnPLTf+Fhg9U97NGjm/awmCLbzLEPbT8QW\r\n" \
    "0JsMcYexB2uG3Y+gsftm2tjL6fLwZeWO2BzqL7otZPFe0BtQsgyFSs87yC4qanWM\r\n" \
    "wK5c2enAfH182pzjvUqwYAeCK31dyBCvLmKM3Jr94dm5WUiXQhrDUIELH4Mia+Sb\r\n" \
    "vCkigv2AUVx1Xw41wt1/L3pnnz2OW4y7r530zAz7qB+dIcHz51IaXc4UV21QuEnu\r\n" \
    "sQsn0uJpJxJuxsAmPuekKxuLUzgG+hqHOuBLf5kWTlk9WWnxcadlZRsCAwEAAaOC\r\n" \
    "AUIwggE+MB0GA1UdDgQWBBR6e4zBz+egyhzUa/r74TPDDxqinTAfBgNVHSMEGDAW\r\n" \
    "gBTlnVkwgkdYzKz6CFQ2hns6tQRN8DASBgNVHRMBAf8ECDAGAQH/AgEAMA4GA1Ud\r\n" \
    "DwEB/wQEAwIBhjAnBgNVHSUEIDAeBggrBgEFBQcDAQYIKwYBBQUHAwIGCCsGAQUF\r\n" \
    "BwMJMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGln\r\n" \
    "aWNlcnQuY29tMDoGA1UdHwQzMDEwL6AtoCuGKWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0\r\n" \
    "LmNvbS9PbW5pcm9vdDIwMjUuY3JsMD0GA1UdIAQ2MDQwMgYEVR0gADAqMCgGCCsG\r\n" \
    "AQUFBwIBFhxodHRwczovL3d3dy5kaWdpY2VydC5jb20vQ1BTMA0GCSqGSIb3DQEB\r\n" \
    "CwUAA4IBAQAR/nIGOiEKN27I9SkiAmKeRQ7t+gaf77+eJDUX/jmIsrsB4Xjf0YuX\r\n" \
    "/bd38YpyT0k66LMp13SH5LnzF2CHiJJVgr3ZfRNIfwaQOolm552W95XNYA/X4cr2\r\n" \
    "du76mzVIoZh90pMqT4EWx6iWu9El86ZvUNoAmyqo9DUA4/0sO+3lFZt/Fg/Hjsk2\r\n" \
    "IJTwHQG5ElBQmYHgKEIsjnj/7cae1eTK6aCqs0hPpF/kixj/EwItkBE2GGYoOiKa\r\n" \
    "3pXxWe6fbSoXdZNQwwUS1d5ktLa829d2Wf6l1uVW4f5GXDuK+OwO++8SkJHOIBKB\r\n" \
    "ujxS43/jQPQMQSBmhxjaMmng9tyPKPK3\r\n"                                 \
    "-----END CERTIFICATE-----\r\n"

#define APP3_PARAMETER_BLOB_VALUE_3_NEW   "App3_Blob: Hello World!_3_NEW"

//App4
#define TEST_APP4   "TestApp4"
#define DOMAIN_APP4 "Domain_App4"

#define APP4_PARAMETER_32_NAME_0       "App4_Parameter_32_0"
#define APP4_PARAMETER_32_VALUE_0      0x44
#define APP4_PARAMETER_32_VALUE_0_NEW  0x7CF324

#define APP4_PARAMETER_32_NAME_1       "App4_Parameter_32_1"
#define APP4_PARAMETER_32_VALUE_1      0x100004
#define APP4_PARAMETER_32_VALUE_1_NEW  0x6215E4

#define APP4_PARAMETER_32_NAME_2       "App4_Parameter_32_2"
#define APP4_PARAMETER_32_VALUE_2      0x80000004
#define APP4_PARAMETER_32_VALUE_2_NEW  0x217724

#define APP4_PARAMETER_32_NAME_3       "App4_Parameter_32_3"
#define APP4_PARAMETER_32_VALUE_3      0xFFFFFFF4
#define APP4_PARAMETER_32_VALUE_3_NEW  0x1A24E4


#define APP4_PARAMETER_64_NAME_0       "App4_Parameter_64_0"
#define APP4_PARAMETER_64_VALUE_0      0x20004
#define APP4_PARAMETER_64_VALUE_0_NEW  0x3CB6C4

#define APP4_PARAMETER_64_NAME_1       "App4_Parameter_64_1"
#define APP4_PARAMETER_64_VALUE_1      0x106CF3B644
#define APP4_PARAMETER_64_VALUE_1_NEW  0x781F4

#define APP4_PARAMETER_64_NAME_2       "App4_Parameter_64_2"
#define APP4_PARAMETER_64_VALUE_2      0x2000000004
#define APP4_PARAMETER_64_VALUE_2_NEW  0x368674

#define APP4_PARAMETER_64_NAME_3       "App4_Parameter_64_3"
#define APP4_PARAMETER_64_VALUE_3      0xAABBCCDD00112234
#define APP4_PARAMETER_64_VALUE_3_NEW  0x128814


#define APP4_PARAMETER_STRING_NAME_0      "App4_Parameter_String_0"
#define APP4_PARAMETER_STRING_VALUE_0     "App4_Hello_World!_0"
#define APP4_PARAMETER_STRING_VALUE_0_NEW "App4_Hello_World!_0_NEW"

#define APP4_PARAMETER_STRING_NAME_1      "App4_Parameter_String_1"
#define APP4_PARAMETER_STRING_VALUE_1     "App4_Hello_World!_1"
#define APP4_PARAMETER_STRING_VALUE_1_NEW "App4_Hello_World!_1_NEW"

#define APP4_PARAMETER_STRING_NAME_2      "App4_Parameter_String_2"
#define APP4_PARAMETER_STRING_VALUE_2     "App4_Hello_World!_2"
#define APP4_PARAMETER_STRING_VALUE_2_NEW "App4_Hello_World!_2_NEW"

#define APP4_PARAMETER_STRING_NAME_3      "App4_Parameter_String_3"
#define APP4_PARAMETER_STRING_VALUE_3     "App4_Hello_World!_3"
#define APP4_PARAMETER_STRING_VALUE_3_NEW "App4_Hello_World!_3_NEW"


#define APP4_PARAMETER_BLOB_NAME_0        "App4_Parameter_Blob_0"
#define APP4_PARAMETER_BLOB_VALUE_0       "App4_Blob: Hello World!_0"
#define APP4_PARAMETER_BLOB_VALUE_0_NEW   "App4_Blob: Hello World!_0_NEW"

#define APP4_PARAMETER_BLOB_NAME_1        "App4_Parameter_Blob_1"
#define APP4_PARAMETER_BLOB_VALUE_1       "App4_Blob: Hello World!_1"
#define APP4_PARAMETER_BLOB_VALUE_1_NEW   "App4_Blob: Hello World!_1_NEW"

#define APP4_PARAMETER_BLOB_NAME_2        "App4_Parameter_Blob_2"
#define APP4_PARAMETER_BLOB_VALUE_2       "App4_Blob: Hello World!_2"
#define APP4_PARAMETER_BLOB_VALUE_2_NEW   "App4_Blob: Hello World!_2_NEW"

#define APP4_PARAMETER_BLOB_NAME_3    "App4_Parameter_Blob_3"
#define APP4_PARAMETER_BLOB_VALUE_3                                           \
    "-----BEGIN CERTIFICATE-----\r\n"                                     \
    "MIIFtDCCBJygAwIBAgIQC2qzsD6xqfbEYJJqqM3+szANBgkqhkiG9w0BAQsFADBa\r\n" \
    "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n" \
    "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTE2\r\n" \
    "MDUyMDEyNTIzOFoXDTI0MDUyMDEyNTIzOFowgYsxCzAJBgNVBAYTAlVTMRMwEQYD\r\n" \
    "VQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNy\r\n" \
    "b3NvZnQgQ29ycG9yYXRpb24xFTATBgNVBAsTDE1pY3Jvc29mdCBJVDEeMBwGA1UE\r\n" \
    "AxMVTWljcm9zb2Z0IElUIFRMUyBDQSA0MIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\r\n" \
    "MIICCgKCAgEAq+XrXaNrOZ71NIgSux1SJl19CQvGeY6rtw7fGbLd7g/27vRW5Ebi\r\n" \
    "kg/iZwvjHHGk1EFztMuZFo6/d32wrx5s7XEuwwh3Sl6Sruxa0EiB0MXpoPV6jx6N\r\n" \
    "XtOtksDaxpE1MSC5OQTNECo8lx0AnpkYGAnPS5fkyfwA8AxanTboskDBSqyEKKo9\r\n" \
    "Rhgrp4qs9K9LqH5JQsdiIMDmpztd65Afu4rYnJDjOrFswpTOPjJry3GzQS65xeFd\r\n" \
    "2FkngvvhSA1+6ATx+QEnQfqUWn3FMLu2utcRm4j6AcxuS5K5+Hg8y5xomhZmiNCT\r\n" \
    "sCqDLpcRHX6BIGHksLmbnG5TlZUixtm9dRC62XWMPD8d0Jb4M0V7ex9UM+VIl6cF\r\n" \
    "JKLb0dyVriAqfZaJSHuSetAksd5IEfdnPLTf+Fhg9U97NGjm/awmCLbzLEPbT8QW\r\n" \
    "0JsMcYexB2uG3Y+gsftm2tjL6fLwZeWO2BzqL7otZPFe0BtQsgyFSs87yC4qanWM\r\n" \
    "wK5c2enAfH182pzjvUqwYAeCK31dyBCvLmKM3Jr94dm5WUiXQhrDUIELH4Mia+Sb\r\n" \
    "vCkigv2AUVx1Xw41wt1/L3pnnz2OW4y7r530zAz7qB+dIcHz51IaXc4UV21QuEnu\r\n" \
    "sQsn0uJpJxJuxsAmPuekKxuLUzgG+hqHOuBLf5kWTlk9WWnxcadlZRsCAwEAAaOC\r\n" \
    "AUIwggE+MB0GA1UdDgQWBBR6e4zBz+egyhzUa/r74TPDDxqinTAfBgNVHSMEGDAW\r\n" \
    "gBTlnVkwgkdYzKz6CFQ2hns6tQRN8DASBgNVHRMBAf8ECDAGAQH/AgEAMA4GA1Ud\r\n" \
    "DwEB/wQEAwIBhjAnBgNVHSUEIDAeBggrBgEFBQcDAQYIKwYBBQUHAwIGCCsGAQUF\r\n" \
    "BwMJMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGln\r\n" \
    "aWNlcnQuY29tMDoGA1UdHwQzMDEwL6AtoCuGKWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0\r\n" \
    "LmNvbS9PbW5pcm9vdDIwMjUuY3JsMD0GA1UdIAQ2MDQwMgYEVR0gADAqMCgGCCsG\r\n" \
    "AQUFBwIBFhxodHRwczovL3d3dy5kaWdpY2VydC5jb20vQ1BTMA0GCSqGSIb3DQEB\r\n" \
    "CwUAA4IBAQAR/nIGOiEKN27I9SkiAmKeRQ7t+gaf77+eJDUX/jmIsrsB4Xjf0YuX\r\n" \
    "/bd38YpyT0k66LMp13SH5LnzF2CHiJJVgr3ZfRNIfwaQOolm552W95XNYA/X4cr2\r\n" \
    "du76mzVIoZh90pMqT4EWx6iWu9El86ZvUNoAmyqo9DUA4/0sO+3lFZt/Fg/Hjsk2\r\n" \
    "IJTwHQG5ElBQmYHgKEIsjnj/7cae1eTK6aCqs0hPpF/kixj/EwItkBE2GGYoOiKa\r\n" \
    "3pXxWe6fbSoXdZNQwwUS1d5ktLa829d2Wf6l1uVW4f5GXDuK+OwO++8SkJHOIBKB\r\n" \
    "ujxS43/jQPQMQSBmhxjaMmng9tyPKPK4\r\n"                                 \
    "-----END CERTIFICATE-----\r\n"

#define APP4_PARAMETER_BLOB_VALUE_3_NEW   "App4_Blob: Hello World!_3_NEW"

#define TEST_APP_SERVER_NO_INIT   "TestAppServerNoInit"
#define DOMAIN_APP_SERVER_NO_INIT "Domain_AppServerNoInit"
