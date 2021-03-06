#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdProc.h"

//建议这样引用，避免下面用关键字时需要加前缀 testing::
using namespace testing;

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

//说明：经过改造后的gtest+，测试套和测试用例名字不允许为空
//      请避免用和gtest相同的关键字，避免不必要的麻烦
//      gtest提供 EXPECT 和 ASSERT 两套,具体含义可以看胶片，两套宏都是一一对应的，下面以EXPECT为例

//1、比对布尔类型 EXPECT_TRUE　EXPECT_FALSE/ASSERT_TRUE
//2、比较整形 EXPECT_EQ EXPECT_NE
//3、比较字符串 EXPECT_STREQ
//4、设置失败输出信息 ADD_FAILUREd
//5、设置成功和失败 SUCCEED FAIL
//6、自定义格式 EXPECT_PRED_FORMAT3
//7、期望带入参数返回TRUE EXPECT_PRED1
//8、浮点型比较 EXPECT_FLOAT_EQ EXPECT_PRED_FORMAT2 ASSERT_PRED_FORMAT2
//9、类型检查 StaticAssertTypeEq
//10、设置3种测试级别事件
//11、获取测试用例名字 test_case_name()
//12、比较异常 EXPECT_THROW
//13、结构体类型比较ASSERT_SAME_DATA ASSERT_SAME_MEMORY

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



class Test_At_HandleApModemSpecialCmd: public ::testing::Test
{
public:
    VOS_UINT8           *pucSystemAppConfigAddr;

    void SetUp()
    {
        UT_STUB_INIT();

        PS_MEM_SET(&g_stATParseCmd, 0, sizeof(AT_PARSECMD_STRU));
        gucAtCmdFmtType = AT_CMD_TYPE_BUTT;
        PS_MEM_SET(g_stParseContext, 0,AT_MAX_CLIENT_NUM * sizeof(AT_CLIENT_MANAGE_STRU));
        PS_MEM_SET(gastAtClientTab, 0,AT_MAX_CLIENT_NUM * sizeof(AT_CLIENT_MANAGE_STRU) );

        At_ParseInit();

        AT_InitPort();
        pucSystemAppConfigAddr = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfigAddr = SYSTEM_APP_ANDROID;
    }
    void TearDown()
    {
    }
};


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_000)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                                   ucIndex = 0;
    VOS_CHAR                               *pucData = VOS_NULL_PTR;
    VOS_UINT16                              usLen = 0;
    VOS_UINT16                              i;

    *pucSystemAppConfigAddr = SYSTEM_APP_MP;
    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_001)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }
    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),
              any(),
              eq((VOS_UINT16)DRV_AGENT_FACAUTHPUBKEY_SET_REQ),
              mirror((void *)&stFacAuthPubkeySetReq, sizeof(DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU)),
              any(),
              any())
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_002)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN - 1;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_003)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_004)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEZ=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }
    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_005)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababa,abababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }
    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_006)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN - 1;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababa,abababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababababababababababababababababababababdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }
    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_007)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    VOS_UINT8                               *pucTmpMem;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_008)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    MOCKER(AT_SaveCmdElementInfo)
        .expects(exactly(1));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_009)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = AT_CLIENT_TAB_APP_INDEX;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=Hbabababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq((VOS_UINT32)AT_CME_INCORRECT_PARAMETERS));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_010)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = AT_CLIENT_TAB_APP_INDEX;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdzdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq(AT_CME_INCORRECT_PARAMETERS));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_011)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }
    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),
              any(),
              eq(DRV_AGENT_FACAUTHPUBKEY_SET_REQ),
              mirror(&stFacAuthPubkeySetReq, sizeof(DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU)),
              any(),
              any())
        .will(returnValue(TAF_FAILURE));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq(AT_ERROR));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_012)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^FACAUTHPUBKEY=") + AT_FACAUTHPUBKEY_PARA_LEN
         + VOS_StrLen(",") + AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    pucData = "AT^FACAUTHPUBKEY=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababab,\
cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd";

    for(i = 0; i< DRV_AGENT_PUBKEY_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKey[i] = 0xab;
    }

    for(i = 0; i< DRV_AGENT_PUBKEY_SIGNATURE_LEN; i++)
    {
        stFacAuthPubkeySetReq.aucPubKeySign[i] = 0xcd;
    }
    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),
              any(),
              eq(DRV_AGENT_FACAUTHPUBKEY_SET_REQ),
              mirror(&stFacAuthPubkeySetReq, sizeof(DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU)),
              any(),
              any())
        .will(returnValue(TAF_SUCCESS));

    MOCKER(At_StartTimer)
        .stubs()
        .will(returnValue(AT_FAILURE));


    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_013)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITE=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),
              any(),
              eq(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ),
              mirror(&stSimlockDataWriteSetReq, sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU)),
              any(),
              any())
        .will(returnValue(TAF_SUCCESS));

    MOCKER(At_StartTimer)
        .stubs()
        .will(returnValue(AT_SUCCESS));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_014)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN - 1;

    pucData = "AT^SIMLOCKDATAWRITE=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    // 初始化全局变量;

    // MOCKER操作;
    //MOCKER(AT_FillAndSndAppReqMsg)
    //    .with(any(),
    //        any(),
    //        eq(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ),
    //        mirror(&stSimlockDataWriteSetReq, sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU)),
    //        any(),
    //        any())
    //    .will(returnValue(TAF_SUCCESS));

    //MOCKER(At_StartTimer)
    //  .will(returnValue(AT_SUCCESS));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_015)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITE=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    // 初始化全局变量;

    // MOCKER操作;
    //MOCKER(AT_FillAndSndAppReqMsg)
    //    .with(any(),
    //        any(),
    //        eq(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ),
    //        mirror(&stSimlockDataWriteSetReq, sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU)),
    //        any(),
    //        any())
    //    .will(returnValue(TAF_SUCCESS));

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_016)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITF=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    // 初始化全局变量;

    // MOCKER操作;
    //MOCKER(AT_FillAndSndAppReqMsg)
    //    .with(any(),
    //        any(),
    //        eq(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ),
    //        mirror(&stSimlockDataWriteSetReq, sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU)),
    //        any(),
    //        any())
    //    .will(returnValue(TAF_SUCCESS));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_017)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                                   ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    VOS_UINT8                                  *pucTmpMem;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITE=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}




TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_018)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                                   ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    VOS_UINT8                                  *pucTmpMem;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITE=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    pucTmpMem = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, VOS_StrLen("AT^SIMLOCKDATAWRITE="));

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_019)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = AT_CLIENT_TAB_APP_INDEX;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    VOS_UINT8                                  *pucTmpMem;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITE=Hbabababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    pucTmpMem = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, VOS_StrLen("AT^SIMLOCKDATAWRITE="));

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq((VOS_UINT32)AT_CME_INCORRECT_PARAMETERS));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_020)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                                   ucIndex = 0;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    VOS_UINT8                                  *pucTmpMem;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITE=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    pucTmpMem = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, VOS_StrLen("AT^SIMLOCKDATAWRITE="));

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),
              any(),
              eq(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ),
              mirror((void *)&stSimlockDataWriteSetReq, sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU)),
              any(),
              any())
        .will(returnValue(TAF_FAILURE));

    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(),eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_HandleApModemSpecialCmd, Test_At_HandleApModemSpecialCmd_021)
{
    // 变量声明
    VOS_UINT32                              ulRet = AT_FAILURE;
    VOS_UINT8                               ucIndex = AT_CLIENT_TAB_APP_INDEX;
    VOS_CHAR                               *pucData;
    VOS_UINT16                              usLen;
    VOS_UINT16                              i;
    VOS_UINT8                                  *pucTmpMem;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;


    // 参数初始化
    usLen = VOS_StrLen("AT^SIMLOCKDATAWRITE=") + AT_SIMLOCKDATAWRITE_PARA_LEN;

    pucData = "AT^SIMLOCKDATAWRITE=ababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
ababababababababababababababababababababababababababababababababababababababababababababab\
abababababababababababababababababababababababab";

    for(i = 0; i< DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN; i++)
    {
        stSimlockDataWriteSetReq.aucCategoryData[i] = 0xab;
    }

    pucTmpMem = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, VOS_StrLen("AT^SIMLOCKDATAWRITE="));

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .with(any(),
              any(),
              eq((VOS_UINT16)DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ),
              mirror((void *)&stSimlockDataWriteSetReq, sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU)),
              any(),
              any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(),eq(AT_ERROR));

    MOCKER(At_StartTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    // 调用被测函数
    ulRet = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulRet);

    GlobalMockObject::verify();
}


class Test_At_ProcXmlText: public ::testing::Test
{
public:
	VOS_UINT8                           ucIndex;
	VOS_UINT8                           aucData[AT_XML_MAX_LEN + 2];
	VOS_UINT16                          usLen;

    void SetUp()
    {
        UT_STUB_INIT();

		usLen = AT_XML_MAX_LEN + 2;
		memset(aucData, 0x31, usLen);

		ucIndex = AT_CLIENT_TAB_APP_INDEX;

		AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_XML_MAX_LEN);
		AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextCur = AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead;
    }

    void TearDown()
    {
        if (VOS_NULL_PTR != AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead)
        {
            PS_MEM_FREE(WUEPS_PID_AT, AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead);
            AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextHead     = VOS_NULL_PTR;
            AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->stXml.pcXmlTextCur      = VOS_NULL_PTR;
        }
    }

};


TEST_F(Test_At_ProcXmlText, Test_At_ProcXmlText_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    usLen                               = AT_XML_MAX_LEN - 101;
    aucData[usLen - 2]                  = ucAtS3;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(V_MemAlloc)
        .expects(exactly(1))
        .will(returnValue((void *)VOS_NULL_PTR));

    // 调用被测函数
    At_ProcXmlText(ucIndex, aucData, usLen);

    //再次调用被测函数
    usLen                               = 100;
    aucData[usLen - 1]                      = AT_CTRL_Z;
    ulRet = At_ProcXmlText(ucIndex, aucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_ProcXmlText, Test_At_ProcXmlText_002)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    usLen                               = 1;
    aucData[0]                          = AT_ESC;

    // 初始化全局变量;

    // MOCKER操作;
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    // 调用被测函数
    ulRet = At_ProcXmlText(ucIndex, aucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_ProcXmlText, Test_At_ProcXmlText_003)
{
    // 变量声明
    VOS_UINT32                          ulRet;

    // 参数初始化
    usLen                               = 1;
    aucData[0]                          = 0x01;

    // 初始化全局变量;

    // MOCKER操作;

    // 调用被测函数
    ulRet = At_ProcXmlText(ucIndex, aucData, usLen);

    // 执行检查
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


#if (FEATURE_ON == FEATURE_AT_HSIC)

class Test_AT_HandleApSecCmd: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfigAddr;

    void SetUp()
    {
        UT_STUB_INIT();

        pucSystemAppConfigAddr  = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfigAddr = SYSTEM_APP_ANDROID;
        Test_AT_InitMuxClientTab();
    }
    void TearDown()
    {
        *pucSystemAppConfigAddr = SYSTEM_APP_MP;
    }
};


TEST_F(Test_AT_HandleApSecCmd, Test_AT_HandleApSecCmd_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MUX1_INDEX;
    pcAtCMD     = "AT^APSEC=00D090781000000102030405060708090A0B0C0D0E0F";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSecCmd, Test_AT_HandleApSecCmd_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MUX4_INDEX;
    pcAtCMD     = "AT^APSEC=00D090781000000102030405060708090A0B0C0D0E0F";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD) + AT_APSEC_CMD_MAX_LEN;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSecCmd, Test_AT_HandleApSecCmd_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MUX4_INDEX;
    pcAtCMD     = "AT^APSEC=00D090781000000102030405060708090A0B0C0D0E0F";
    usLen       = AT_APSEC_CMD_MIN_LEN - 1;

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSecCmd, Test_AT_HandleApSecCmd_004)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MUX4_INDEX;
    pcAtCMD     = "AT^APSEC=00D090781000000102030405060708090A0B0C0D0E0F";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(atMatchCmdName)
        .expects(exactly(1))
        .will(returnValue(ERR_MSP_SUCCESS));

    MOCKER(AT_SetApSecPara)
        .expects(exactly(1))
        .will(returnValue(AT_CME_INCORRECT_PARAMETERS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(AT_CME_INCORRECT_PARAMETERS));

    // 调用被测函数
    ulResult = AT_HandleApSecCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSecCmd, Test_AT_HandleApSecCmd_005)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MUX4_INDEX;
    pcAtCMD     = "AT^APSEC=00D090781000000102030405060708090A0B0C0D0E0F";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(atMatchCmdName)
        .expects(exactly(1))
        .will(returnValue(ERR_MSP_SUCCESS));

    MOCKER(AT_SetApSecPara)
        .expects(exactly(1))
        .will(returnValue(AT_WAIT_ASYNC_RETURN));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulResult = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSecCmd, Test_AT_HandleApSecCmd_006)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MUX4_INDEX;
    pcAtCMD     = "AT^APSEB=00D090781000000102030405060708090A0B0C0D0E0F";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = AT_HandleApSecCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSecCmd, Test_AT_HandleApSecCmd_007)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_MUX4_INDEX;
    pcAtCMD     = "AT^APSEC=00D090781000000102030405060708090A0B0C0D0E0F";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(atMatchCmdName)
        .stubs()
        .will(returnValue(AT_ERROR));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(AT_ERROR));

    // 调用被测函数
    ulResult = AT_HandleApSecCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}
#endif


class Test_AT_HandleApSndApduCmd: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfigAddr;

    void SetUp()
    {
        UT_STUB_INIT();

        pucSystemAppConfigAddr  = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfigAddr = SYSTEM_APP_ANDROID;
        Test_AT_InitMuxClientTab();
    }
    void TearDown()
    {
        *pucSystemAppConfigAddr = SYSTEM_APP_MP;
    }
};


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_PCUI_INDEX;
    pcAtCMD     = "AT^CISA=16,\"000102030405060708090A0B0C0D0E0F\"";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(AT_CheckHsicUser)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // 调用被测函数
    ulResult = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_002)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISB=16,\"000102030405060708090A0B0C0D0E0F\"";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作

    // 调用被测函数
    ulResult = AT_HandleApSndApduCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_FAILURE, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_003)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISA=16,0,\"000102030405060708090A0B0C0D0E0F\"";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(AT_CME_INCORRECT_PARAMETERS));

    // 调用被测函数
    ulResult = AT_HandleApSndApduCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_004)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISA=16,\"000102030405060708090A0B0C0D0E0F";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(AT_CME_INCORRECT_PARAMETERS));

    // 调用被测函数
    ulResult = AT_HandleApSndApduCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_005)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISA=lO,\"000102030405060708090A0B0C0D0E0F\"";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(AT_CME_INCORRECT_PARAMETERS));

    // 调用被测函数
    ulResult = AT_HandleApSndApduCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_006)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISA=16,\"000102030405060708090A0B0C0D0E0F\"";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(atMatchCmdName)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_ERROR));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulResult = AT_HandleApSndApduCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_007)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISA=16,\"000102030405060708090A0B0C0D0E0F\"";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(atMatchCmdName)
        .stubs()
        .will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));

    MOCKER(AT_SetCISAPara)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_ERROR));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq((VOS_UINT32)AT_ERROR));

    // 调用被测函数
    ulResult = AT_HandleApSndApduCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_008)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISA=16,\"000102030405060708090A0B0C0D0E0F\"";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(atMatchCmdName)
        .stubs()
        .will(returnValue((VOS_UINT32)ERR_MSP_SUCCESS));

    MOCKER(AT_SetCISAPara)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_WAIT_ASYNC_RETURN));

    MOCKER(At_FormatResultData)
        .expects(never());

    // 调用被测函数
    ulResult = At_HandleApModemSpecialCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_HandleApSndApduCmd, Test_AT_HandleApSndApduCmd_009)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    VOS_CHAR                           *pcAtCMD;
    VOS_UINT16                          usLen;
    VOS_UINT32                          ulResult;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_APP_INDEX;
    pcAtCMD     = "AT^CISA=?";
    usLen       = (VOS_UINT16)VOS_StrLen(pcAtCMD);

    // 初始化全局变量

    // MOCKER操作
    MOCKER(atMatchCmdName)
        .expects(never());

    MOCKER(AT_SetCISAPara)
        .expects(never());

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(eq(ucIndex), eq(AT_ERROR));

    // 调用被测函数
    ulResult = AT_HandleApSndApduCmd(ucIndex, (VOS_UINT8 *)pcAtCMD, usLen);

    // 执行检查
    EXPECT_EQ(AT_SUCCESS, ulResult);

    GlobalMockObject::verify();
}




class Test_At_InterTimerOutProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_ABORT_CMD_PARA_STRU             *pstAbortCmdPara;

        At_PidInit(VOS_IP_INITIAL);

        pstAbortCmdPara = AT_GetAbortCmdPara();

        pstAbortCmdPara->ucAbortEnableFlg = VOS_TRUE;

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtCmdStr, "AT");

        VOS_StrCpy((VOS_CHAR *)pstAbortCmdPara->aucAbortAtRspStr, "ABORT");

        PS_MEM_SET(&gstAtSendData, 0x00, sizeof(AT_SEND_DATA_BUFFER_STRU));

        At_ResetCombinParseInfo(0);
    }

    void TearDown()
    {

    }
};


TEST_F(Test_At_InterTimerOutProc, Test_At_InterTimerOutProc_001)
{
    VOS_UINT8                           aucMsgCops[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x12,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x0A,0x00,0x41,0x54,0x2B,0x43,0x4F,0x50,0x53,0x3D,
        0x3F,0x0D
    };

    VOS_UINT8                           aucMsgAt[] =
    {
        0x00,0x00,0x00,0x00,0x0D,0x01,0x00,0x00,0x00,0x00,
        0x00,0x00,0x0D,0x01,0x00,0x00,0x0B,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x03,0x00,0x41,0x54,0x0D
    };
    VOS_UINT8                           aucDataAt[20];
    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucDataAt;
    VOS_UINT32                          ulTmp;

    VOS_UINT32                          ulTick;

    ulTick    = VOS_GetTick();

    /* 构造ABORT返回结果 */
    usLength  = 0;
    ulTmp     = 0;

    PS_MEM_SET(aucDataAt, 0x00, sizeof(aucDataAt));

    pucDataAt = aucDataAt;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    ulTmp = VOS_StrLen((VOS_CHAR *)AT_GetAbortRspStr());
    PS_MEM_CPY( (pucDataAt + usLength), (VOS_CHAR *)AT_GetAbortRspStr(), ulTmp );
    usLength += (VOS_UINT16)ulTmp;

    PS_MEM_CPY((pucDataAt + usLength), (VOS_CHAR *)gaucAtCrLf, 2);
    usLength += 2;

    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    AT_STOP_TIMER_CMD_READY(0);

    /* 进入测试流程 */
    MOCKER(LimitedCmdProc)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_OK));

    At_MsgProc((MsgBlock *)aucMsgCops);

    ulTick += 10000;

    MOCKER(VOS_GetTick)
        .stubs()
        .will(returnValue(ulTick));

    At_MsgProc((MsgBlock *)aucMsgAt);

    At_InterTimerOutProc(0);

    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[0].CmdCurrentOpt);

    EXPECT_STREQ((char*)pgucAtSndCodeAddr, (char*)aucDataAt);

}

TEST_F(Test_At_InterTimerOutProc, Test_At_InterTimerOutProc_002)
{
    VOS_UINT8                           ucIndex = 0;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;
    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* 桩函数*/
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq((VOS_UINT32)AT_CME_NETWORK_TIMEOUT));

    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    AT_STOP_TIMER_CMD_READY(0);

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CUSD_REQ;

    /* 调用函数 */
    At_InterTimerOutProc(ucIndex);

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}



TEST_F(Test_At_InterTimerOutProc, Test_At_InterTimerOutProc_003)
{
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulResult = AT_ABORT;

    /* 桩函数*/
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(ulResult));

    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    AT_STOP_TIMER_CMD_READY(0);

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ABORT_NETSCAN;

    /* 调用函数 */
    At_InterTimerOutProc(ucIndex);

    /* 检查结果 */

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_InterTimerOutProc, Test_At_InterTimerOutProc_004)
{
    // 变量声明
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    AT_MODE_TYPE                        ucMode;
    VOS_UINT8                           ucSubMode;

    // 参数初始化
    ulResult = AT_ERROR;
    ucIndex  = AT_CLIENT_TAB_HSUART_INDEX;

    // 初始化全局变量

    // MOCKER操作
    MOCKER(At_FormatResultData)
        .stubs()
        .with(eq(ucIndex), eq(ulResult));

    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    AT_STOP_TIMER_CMD_READY(0);

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;

    // 调用被测函数
    At_InterTimerOutProc(ucIndex);

    // 执行检查
    EXPECT_EQ(AT_CMD_MODE, gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_DATA_BUTT_MODE, gastAtClientTab[ucIndex].DataMode);
    EXPECT_EQ(AT_DATA_STOP_STATE, gastAtClientTab[ucIndex].DataState);

    GlobalMockObject::verify();
}


class Test_At_SendPduMsgAck: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SendPduMsgAck, Test_At_SendPduMsgAck_001)
{
    // 变量声明
    VOS_UINT32                          ulRet;
    TAF_UINT8                           ucIndex;
    TAF_UINT8                           aucPdu[] = {0x00, 0xd3, 0x00};
    TAF_UINT32                          ulLen;

    //参数初始化
    ucIndex = 0;
    ulLen   = 3;

    // 初始化全局变量
    gastAtClientTab[ucIndex].AtSmsData.ucPduLen = 3;
    gastAtClientTab[ucIndex].AtSmsData.ucCnmaType = 2;
    gastAtClientTab[ucIndex].usClientId = 0;

    // MOCKER操作
    MOCKER(MN_MSG_SendAck)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    // 调用被测函数
    ulRet = At_SendPduMsgAck(ucIndex, aucPdu, ulLen);

    // 执行检查
    EXPECT_EQ(AT_CMD_CNMA_PDU_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}




class Test_At_ClientIdToUserId: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_ClientIdToUserId,Test_At_ClientIdToUserId_001)
{
    TAF_UINT16                              usClientId;
    TAF_UINT8                               ucIndexId;
    TAF_UINT32                              ulRst;

    usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;

    MOCKER(VOS_SmBCreate)
        .defaults()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_GetLength)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    At_PidInit(VOS_IP_INITIAL);

    ulRst = At_ClientIdToUserId(usClientId, &ucIndexId);

    EXPECT_EQ(AT_BROADCAST_CLIENT_INDEX_MODEM_0, ucIndexId);
    EXPECT_EQ(AT_SUCCESS, ulRst);

    GlobalMockObject::verify();
}


TEST_F(Test_At_ClientIdToUserId,Test_At_ClientIdToUserId_002)
{
    TAF_UINT16                              usClientId;
    TAF_UINT8                               ucIndexId;
    TAF_UINT32                              ulRst;

    usClientId = AT_BROADCAST_CLIENT_ID_MODEM_1;

    MOCKER(VOS_SmBCreate)
        .defaults()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_GetLength)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    At_PidInit(VOS_IP_INITIAL);

    ulRst = At_ClientIdToUserId(usClientId, &ucIndexId);

    EXPECT_EQ(AT_BROADCAST_CLIENT_INDEX_MODEM_1, ucIndexId);
    EXPECT_EQ(AT_SUCCESS, ulRst);

    GlobalMockObject::verify();
}


TEST_F(Test_At_ClientIdToUserId,Test_At_ClientIdToUserId_003)
{
    TAF_UINT16                              usClientId;
    TAF_UINT8                               ucIndexId;
    TAF_UINT32                              ulRst;

    usClientId = AT_CLIENT_ID_APP;

    MOCKER(VOS_SmBCreate)
        .defaults()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_GetLength)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    At_PidInit(VOS_IP_INITIAL);

    ulRst = At_ClientIdToUserId(usClientId, &ucIndexId);

    EXPECT_EQ(AT_CLIENT_TAB_APP_INDEX, ucIndexId);
    EXPECT_EQ(AT_SUCCESS, ulRst);

    GlobalMockObject::verify();
}


TEST_F(Test_At_ClientIdToUserId,Test_At_ClientIdToUserId_004)
{
    TAF_UINT16                              usClientId;
    TAF_UINT8                               ucIndexId;
    TAF_UINT32                              ulRst;

    usClientId = AT_CLIENT_ID_BUTT;

    MOCKER(VOS_SmBCreate)
        .defaults()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_GetLength)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    At_PidInit(VOS_IP_INITIAL);

    ulRst = At_ClientIdToUserId(usClientId, &ucIndexId);

    EXPECT_EQ(AT_FAILURE, ulRst);

    GlobalMockObject::verify();
}


class Test_At_CheckUsimStatus: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_CheckUsimStatus,Test_At_CheckUsimStatus_001)
{
    // 参数定义
    TAF_UINT8                           aucCmdName[15] = "+COPS";
    VOS_UINT8                           ucIndex;
    TAF_UINT32                          ulQuickStartFlg;
    VOS_UINT32                          ulRst;

    // 参数初始化
    ucIndex = 0;

    // 相关全局变量初始化
    ulQuickStartFlg = AT_QUICK_START_ENABLE;

    // MOCKER操作;
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .will(returnValue(VOS_ERR));

    // 调用被测函数
    ulRst = At_CheckUsimStatus(aucCmdName, ucIndex);

    // 执行检查
    EXPECT_EQ(ulRst,AT_ERROR);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUsimStatus,Test_At_CheckUsimStatus_002)
{
    // 参数定义
    TAF_UINT8                           aucCmdName[15] = "+CMGL";
    VOS_UINT8                           ucIndex;
    TAF_UINT32                          ulQuickStartFlg;
    VOS_UINT32                          ulRst;
    AT_CLIENT_CTX_STRU                 *pstClientCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 1;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_1);
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 0;
#endif

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(MODEM_ID_0);
    pstUsimInfoCtx->enCardStatus = USIMM_CARD_SERVIC_SIM_PIN;

    // 相关全局变量初始化
    ulQuickStartFlg = AT_QUICK_START_DISABLE;

    enModemId = MODEM_ID_0;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemId))
        .will(returnValue((VOS_UINT32)NV_OK));


    // 调用被测函数
    ulRst = At_CheckUsimStatus(aucCmdName, ucIndex);

    // 执行检查
    EXPECT_EQ(ulRst,AT_SUCCESS);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_CheckUsimStatus,Test_At_CheckUsimStatus_003)
{
    // 参数定义
    TAF_UINT8                           aucCmdName[15] = "+COPS";
    VOS_UINT8                           ucIndex;
    TAF_UINT32                          ulQuickStartFlg;
    VOS_UINT32                          ulRst;
    AT_CLIENT_CTX_STRU                 *pstClientCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(MODEM_ID_0);
    pstUsimInfoCtx->enCardStatus = USIMM_CARD_SERVIC_SIM_PIN;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(MODEM_ID_1);
    pstUsimInfoCtx->enCardStatus = USIMM_CARD_SERVIC_AVAILABLE;
#endif

    // 相关全局变量初始化
    ulQuickStartFlg = AT_QUICK_START_DISABLE;

    enModemId = MODEM_ID_0;

    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemId))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRst = At_CheckUsimStatus(aucCmdName, ucIndex);

    // 执行检查
    EXPECT_EQ(ulRst,AT_CME_SIM_PIN_REQUIRED);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_CheckUsimStatus,Test_At_CheckUsimStatus_004)
{
    // 参数定义
    TAF_UINT8                           aucCmdName[15] = "+COPS";
    VOS_UINT8                           ucIndex;
    TAF_UINT32                          ulQuickStartFlg;
    VOS_UINT32                          ulRst;
    AT_CLIENT_CTX_STRU                 *pstClientCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;

    // 参数初始化
    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;

    pstClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(MODEM_ID_1);
    pstUsimInfoCtx->enCardStatus = USIMM_CARD_SERVIC_SIM_PIN;

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(MODEM_ID_0);
    pstUsimInfoCtx->enCardStatus = USIMM_CARD_SERVIC_AVAILABLE;

    // 相关全局变量初始化
    ulQuickStartFlg = AT_QUICK_START_DISABLE;

    enModemId = MODEM_ID_1;
    // MOCKER操作;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemId))
        .will(returnValue((VOS_UINT32)NV_OK));

    // 调用被测函数
    ulRst = At_CheckUsimStatus(aucCmdName, ucIndex);

    // 执行检查
    EXPECT_EQ(ulRst,AT_CME_SIM_PIN_REQUIRED);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_TimeOutProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_TimeOutProc, Test_At_TimeOutProc_003)
{
    REL_TIMER_MSG                        *pMsg;
    VOS_UINT8                           ucIndex = 0;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_0;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pMsg = (REL_TIMER_MSG*)PS_ALLOC_MSG_WITH_HEADER_LEN(VOS_PID_TIMER, sizeof(REL_TIMER_MSG));
    memset(pMsg, 0, sizeof(REL_TIMER_MSG));

    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = VOS_PID_TIMER;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->ulName = 0x00000101;

    /* 桩函数 */
    MOCKER(MN_CALL_Sups)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 处理函数 */
    At_MsgProc((MsgBlock*)pMsg);

    /* 检查结果 */
    EXPECT_EQ(TAF_FALSE, pstCcCtx->stS0TimeInfo.bTimerStart);

    PS_MEM_FREE(VOS_PID_TIMER, pMsg);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_TimeOutProc, Test_At_TimeOutProc_004)
{
    REL_TIMER_MSG                        *pMsg;
    VOS_UINT8                           ucIndex = 0;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_1;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = enModemId;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pMsg = (REL_TIMER_MSG*)PS_ALLOC_MSG_WITH_HEADER_LEN(VOS_PID_TIMER, sizeof(REL_TIMER_MSG));
    memset(pMsg, 0, sizeof(REL_TIMER_MSG));

    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = VOS_PID_TIMER;
    pMsg->ulReceiverPid   = WUEPS_PID_AT;

    pMsg->ulName = 0x00000101;

    /* 桩函数 */
    MOCKER(MN_CALL_Sups)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* 处理函数 */
    At_MsgProc((MsgBlock*)pMsg);

    /* 检查结果 */
    EXPECT_EQ(TAF_FALSE, pstCcCtx->stS0TimeInfo.bTimerStart);

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_SmsProc: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SmsProc,Test_At_SmsProc_001)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;
    AT_CLIENT_CTX_STRU                     *pstAtClientCtx = VOS_NULL_PTR;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"\r\n";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"\r\n") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"\r\n");

    pstAtClientCtx = AT_GetClientCtxAddr(pstMsg->ucIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode             = AT_SMS_MODE;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_TEXT;

    // MOCKER操作;
    MOCKER(At_SmsTextProc).stubs().will(returnValue((TAF_UINT32)AT_WAIT_SMS_INPUT));
    MOCKER(At_FormatResultData).stubs().with(any(), eq((VOS_UINT32)AT_WAIT_SMS_INPUT));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsProc,Test_At_SmsProc_002)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"\r\n";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"\r\n") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;

    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"\r\n");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode             = AT_SMS_MODE;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;

    // MOCKER操作;
    MOCKER(At_SmsPduProc).stubs().will(returnValue((TAF_UINT32)AT_ERROR));
    MOCKER(At_FormatResultData).stubs().with(any(), eq(AT_ERROR));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SmsProc,Test_At_SmsProc_003)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"\r\n";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"\r\n") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"\r\n");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                            = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat                = AT_CMGF_MSG_FORMAT_TEXT;

    // MOCKER操作;
    MOCKER(At_SmsTextProc).stubs().will(returnValue((TAF_UINT32)AT_WAIT_SMS_INPUT));
    MOCKER(At_FormatResultData).stubs().with(any(), eq(AT_WAIT_SMS_INPUT));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsProc,Test_At_SmsProc_004)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"\r\n";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"\r\n") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"\r\n");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                = AT_SMS_MODE;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat    = AT_CMGF_MSG_FORMAT_PDU;

    // MOCKER操作
    MOCKER(At_SmsPduProc).stubs().will(returnValue((TAF_UINT32)AT_ERROR));
    MOCKER(At_FormatResultData).stubs().with(any(), eq(AT_ERROR));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif

class Test_At_SendTextMsgOrCmd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SendTextMsgOrCmd,Test_At_SendTextMsgOrCmd_001)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                                            = AT_SMS_MODE;
    gucAtCscsType                                                                       = AT_CSCS_IRA_CODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId                   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat                                = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt                                      = AT_CMD_CMGS_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen  = 0;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_SMSC_ADDRESS_UNKNOWN));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendTextMsgOrCmd,Test_At_SendTextMsgOrCmd_002)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                                            = AT_SMS_MODE;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat                                = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt                                      = AT_CMD_CMGS_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen  = 1;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_INVALID_TEXT_MODE_PARAMETER));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SendTextMsgOrCmd,Test_At_SendTextMsgOrCmd_003)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                                            = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId                   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat                                = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt                                      = AT_CMD_CMGS_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen  = 0;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_SMSC_ADDRESS_UNKNOWN));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendTextMsgOrCmd,Test_At_SendTextMsgOrCmd_004)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                                            = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId                   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat                                = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt                                      = AT_CMD_CMGS_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen  = 1;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_INVALID_TEXT_MODE_PARAMETER));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif



class Test_At_WriteTextMsgToMem: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_WriteTextMsgToMem,Test_At_WriteTextMsgToMem_001)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                                            = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId                   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat                                = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt                                      = AT_CMD_CMGW_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen  = 0;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_ERROR));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_WriteTextMsgToMem,Test_At_WriteTextMsgToMem_002)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode                                            = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId                   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat                                = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt                                      = AT_CMD_CMGW_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen  = 1;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.SmState                                  = MN_MSG_STATUS_MO_SENT;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_INVALID_TEXT_MODE_PARAMETER));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_WriteTextMsgToMem,Test_At_WriteTextMsgToMem_003)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGW_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 1;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.SmState = MN_MSG_STATUS_NONE;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_ERROR));

    MOCKER(MN_MSG_DecodeDcs).stubs().will(returnValue(MN_ERR_UNSPECIFIED));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_WriteTextMsgToMem,Test_At_WriteTextMsgToMem_004)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "at+cmgs=\"13900000008\"'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("at+cmgs=\"13900000008\"'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("at+cmgs=\"13900000008\"'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_TEXT;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGW_TEXT_SET;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 1;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.SmState = MN_MSG_STATUS_MO_NOT_SENT;

    // MOCKER操作;
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_INVALID_TEXT_MODE_PARAMETER));

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif



class Test_At_SendPduMsgOrCmd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SendPduMsgOrCmd,Test_At_SendPduMsgOrCmd_001)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId = MODEM_ID_0;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGS_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_SIM;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_SMSC_ADDRESS_UNKNOWN));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendPduMsgOrCmd,Test_At_SendPduMsgOrCmd_002)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGS_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 1;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_NONE;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_INVALID_PDU_MODE_PARAMETER));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SendPduMsgOrCmd,Test_At_SendPduMsgOrCmd_003)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGS_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 0;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_SIM;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_SMSC_ADDRESS_UNKNOWN));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_SendPduMsgOrCmd,Test_At_SendPduMsgOrCmd_004)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;
    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGS_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_NONE;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_CMS_INVALID_PDU_MODE_PARAMETER));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


class Test_At_WritePduMsgToMem: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_WritePduMsgToMem,Test_At_WritePduMsgToMem_001)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;

    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGW_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_SIM;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_ERROR));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_WritePduMsgToMem,Test_At_WritePduMsgToMem_002)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;

    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGW_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 1;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_NONE;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_ERROR));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_WritePduMsgToMem,Test_At_WritePduMsgToMem_003)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;

    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;

    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGW_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 0;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_SIM;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));
    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_ERROR));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}


TEST_F(Test_At_WritePduMsgToMem,Test_At_WritePduMsgToMem_004)
{
    // 参数定义
    AT_MSG_STRU                            *pstMsg;
    VOS_CHAR                               *pucData;

    // 参数初始化
    pucData = "0015660B813109120090F60008FF044F60597D'\x1a'\r";

    pstMsg = (AT_MSG_STRU *)malloc((sizeof(AT_MSG_STRU) + sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r") - 4));

    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ucType          = 0;
    pstMsg->ucIndex         = 0;
    pstMsg->ucUserType      = AT_APP_USER;
    pstMsg->usLen           = sizeof("0015660B813109120090F60008FF044F60597D'\x1a'\r");

    memcpy(pstMsg->aucValue, pucData, pstMsg->usLen);

    // 相关全局变量初始化
    g_stParseContext[pstMsg->ucIndex].ucMode = AT_SMS_MODE;

    g_astAtClientCtx[pstMsg->ucIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    gastAtClientTab[pstMsg->ucIndex].CmdCurrentOpt = AT_CMD_CMGW_PDU_SET;
    gastAtClientTab[pstMsg->ucIndex].AtSmsData.ucPduLen = pstMsg->usLen - 4;

    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat = AT_CMGF_MSG_FORMAT_PDU;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stParmInUsim.stScAddr.ucBcdLen = 1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCpmsInfo.enMemSendorWrite = MN_MSG_MEM_STORE_NONE;

    // MOCKER操作;
    MOCKER(At_UnicodePrint2Unicode).stubs().will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .expects(exactly(1))
        .with(any(), eq(AT_ERROR));

    // 调用被测函数
    At_MsgProc((MsgBlock*)pstMsg);
    free(pstMsg);

    // 执行检查

    //检查调用时，需要在用例结束位置加上这句
    GlobalMockObject::verify();
}
#endif


/* 删除私有解析器的UT用例 */



class Test_At_SetMode: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        AT_InitUartCtx();
        At_ParseInit();
    }
    void TearDown()
    {
        AT_InitUartCtx();
        At_ParseInit();
    }
};


TEST_F(Test_At_SetMode, Test_At_SetMode_001)
{
    // 变量声明
    VOS_UINT8                           ucIndex;
    AT_MODE_TYPE                        ucMode;
    VOS_UINT8                           ucSubMode;

    // 参数初始化
    ucIndex     = AT_CLIENT_TAB_HSUART_INDEX;
    ucMode      = AT_ONLINE_CMD_MODE;
    ucSubMode   = AT_NORMAL_MODE;

    // 初始化全局变量
    gastAtClientTab[ucIndex].Mode       = AT_DATA_MODE;
    gastAtClientTab[ucIndex].DataMode   = AT_PPP_DATA_MODE;
    gastAtClientTab[ucIndex].DataState  = AT_DATA_START_STATE;

    // MOCKER操作

    // 调用被测函数
    At_SetMode(ucIndex, ucMode, ucSubMode);

    // 执行检查
    EXPECT_EQ(AT_ONLINE_CMD_MODE, gastAtClientTab[ucIndex].Mode);
    EXPECT_EQ(AT_PPP_DATA_MODE, gastAtClientTab[ucIndex].DataMode);
    EXPECT_EQ(AT_DATA_STOP_STATE, gastAtClientTab[ucIndex].DataState);

    GlobalMockObject::verify();
}

#if 0


class Test_AT_MapCallTypeModeToClccMode: public ::testing::Test
{
    void SetUp()
    {

    }

    void TearDown()
    {

    }
};


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_001)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_VOICE;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(0, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_002)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_EMERGENCY;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(0, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_003)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_MIEC;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(0, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_004)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_AIEC;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(0, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_005)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_TEST;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(0, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_006)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_RECFGURATION;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(0, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_007)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_PSAP_ECALL;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(0, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_008)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_FAX;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(2, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}


TEST_F(Test_AT_MapCallTypeModeToClccMode, Test_AT_MapCallTypeModeToClccMode_009)
{
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           enClccMode;

    enCallType = MN_CALL_TYPE_BUTT;
    enClccMode = 0;

    AT_MapCallTypeModeToClccMode(enCallType, &enClccMode);

    /* 结果验证 */
    ASSERT_EQ(1, enClccMode);

    /* 检查调用时, 需要在用例结束位置加上这句 */
    LLT_GLOBALOBJMOCKER::verify();
}

#endif


