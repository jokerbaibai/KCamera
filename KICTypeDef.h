#ifndef KICTYPEDEF_H
#define KICTYPEDEF_H

typedef enum tagKICRegister
{
    ICReg_Transfer_Mode = 0,   		//图像传输模式
    ICReg_Switch_OnOff,				//相机开关
    ICReg_Trig_Mode,				//触发模式
    ICReg_Frame_Rate,				//帧率
    ICReg_Image_Output,				//图像输出

    ICReg_Frame_Window = 0x05,  	//图像窗口大小设置
    ICReg_Exposure_Mode = 0x06,		//曝光模式
    ICReg_Exposure_Time = 0x09,  	//曝光时间
    ICReg_Analog_Gain = 0x0B,    	//模拟增益
    ICReg_Digital_Gain = 0x0D,   	//数字增益

    ICReg_Light_TrigDelay = 0x0F,	//光源触发延迟
    ICReg_Light_PulseWidth = 0x10,	//光源脉冲宽度
    ICReg_Camera_TrigDelay,			//相机触发延迟
    ICReg_Pixel_OutMode,			//像素输出模式

    ICReg_RDigital_Gain = 0x15,   	//red数字增益
    ICReg_GDigital_Gain,	      	//green数字增益
    ICReg_BDigital_Gain,		 	//blue数字增益

    ICReg_RWhite_Balance = 0x40,
    ICReg_GWhite_Balance = 0x41,
    ICReg_BWhite_Balance = 0x43,

    ICReg_Slaver_Addr = 0x44,
    ICReg_Left_Shield,
    ICReg_Right_Shield,
    ICReg_Shield_Pixel,

    ICReg_CascadeCount = 0x48,    //级联相机个数

    ICReg_Valve_Blow = 0x50,      //吹阀数据
    ICReg_FPGA_Update = 0x60,     //FPGA升级数据
    ICReg_FPGA_EndUpdate,         //升级结束
    ICReg_FPGA_FlashData,         //烧录接口参数
    ICReg_FPGA_ReloadParam,       //重新加载flash参数
    ICReg_Valve_Defend,			  //吹阀保护
    ICReg_Valve_Overlap,          //吹阀重叠
    ICReg_OpticalCalibration,     //光学校准数据

    ICReg_IPC_AlgoDelay0 = 0x70,  //工控算法吹阀延迟0
    ICReg_IPC_AlgoDelay1,			//工控算法吹阀延迟1
    ICReg_IPC_AlgoDelay2,			//工控算法吹阀延迟2
    ICReg_IPC_AlgoDelay3,			//工控算法吹阀延迟3
    ICReg_IPC_AlgoDelay4,			//工控算法吹阀延迟4
    ICReg_IPC_AlgoDelay5,			//工控算法吹阀延迟5
    ICReg_IPC_AlgoDelay6,			//工控算法吹阀延迟6
    ICReg_IPC_AlgoDelay7,			//工控算法吹阀延迟7
    ICReg_IPC_AlgoDelay8,			//工控算法吹阀延迟8
    ICReg_IPC_AlgoDelay9,			//工控算法吹阀延迟9
    ICReg_IPC_AlgoDelay10,			//工控算法吹阀延迟10
    ICReg_IPC_AlgoDelay11,			//工控算法吹阀延迟11
    ICReg_IPC_AlgoDelay12,			//工控算法吹阀延迟12
    ICReg_IPC_AlgoDelay13,			//工控算法吹阀延迟13
    ICReg_IPC_AlgoDelay14,			//工控算法吹阀延迟14
    ICReg_IPC_AlgoDelay15,			//工控算法吹阀延迟15

    ICReg_Firm_Info = 0x80,			//厂商信息
    ICReg_Manufacture_Info,			//制造商信息
    ICReg_Device_Type,				//设备型号
    ICReg_SN_Num,					//SN编号

    ICReg_Valve_Enable = 0x8A,      //阀开关
    ICReg_Blow_Time,                //吹气时间
    ICReg_Charge_Time,              //充电时间
    ICReg_StopCharge_Time,          //停止充电时间
    ICReg_Recharge_Time,            //续充电时间

    ICReg_Src_IP = 0x90,
    ICReg_Dst_IP,
    ICReg_Src_IPMask,
    ICReg_Src_IPGateway,
    ICReg_Src_Mac,
    ICReg_Src_MTU,
    ICReg_Dst_Port,
    ICReg_Src_Port,

    ICReg_IPC_AlgoDelay16 = 0xA0,   //工控算法吹阀延迟16
    ICReg_IPC_AlgoDelay17,			//工控算法吹阀延迟17
    ICReg_IPC_AlgoDelay18,			//工控算法吹阀延迟18
    ICReg_IPC_AlgoDelay19,			//工控算法吹阀延迟19
    ICReg_IPC_AlgoDelay20,			//工控算法吹阀延迟20
    ICReg_IPC_AlgoDelay21,			//工控算法吹阀延迟21
    ICReg_IPC_AlgoDelay22,			//工控算法吹阀延迟22
    ICReg_IPC_AlgoDelay23,			//工控算法吹阀延迟23
    ICReg_IPC_AlgoDelay24,			//工控算法吹阀延迟24
    ICReg_IPC_AlgoDelay25,			//工控算法吹阀延迟25
    ICReg_IPC_AlgoDelay26,			//工控算法吹阀延迟26
    ICReg_IPC_AlgoDelay27,			//工控算法吹阀延迟27
    ICReg_IPC_AlgoDelay28,			//工控算法吹阀延迟28
    ICReg_IPC_AlgoDelay29,			//工控算法吹阀延迟29
    ICReg_IPC_AlgoDelay30,			//工控算法吹阀延迟30
    ICReg_IPC_AlgoDelay31,			//工控算法吹阀延迟31

    //grayM algo params
    ICReg_MGrayMode = 0xB0,         //M框灰度模式
    ICReg_MUpEnable,                //M框灰度上限使能
    ICReg_MDownEnable,              //M框灰度下限使能
    ICReg_MUpThreshold,             //M框灰度上限阈值设置
    ICReg_MDownThreshold,           //M框灰度下限阈值设置
    ICReg_MAixsWidth,               //M框滤波器宽度设置
    ICReg_MAixsHeight,              //M框滤波器高度设置
    ICReg_MAixsArea,                //M框滤波器阈值设置

    //grayN algo params
    ICReg_NGrayMode = 0xB8,         //N框灰度模式
    ICReg_NUpEnable,                //N框灰度上限使能
    ICReg_NDownEnable,              //N框灰度下限使能
    ICReg_NUpThreshold,             //N框灰度上限阈值设置
    ICReg_NDownThreshold,           //N框灰度下限阈值设置
    ICReg_NAixsWidth,               //N框滤波器宽度设置
    ICReg_NAixsHeight,              //N框滤波器高度设置
    ICReg_NAixsArea,                //N框滤波器阈值设置

    //color difM algo params
    ICReg_MColorDif_Enable = 0xC0,  //M框色差算法使能
    ICReg_MColorDif_Mode,           //M框色差模式选择
    ICReg_MColorDif_Sensor,         //M框色差灵敏度
    ICReg_MColorDif_RGB,            //M框色差阈值颜色选择
    ICReg_MColorDif_Upper,          //M框色差阈值--上限
    ICReg_MColorDif_Lower,          //M框色差阈值--下限
    ICReg_MColorDif_Width,          //M框色差宽度设置
    ICReg_MColorDif_Height,         //M框色差高度设置
    ICReg_MColorDif_Threshold,      //M框色差算法阈值设置

    //color difN algo params
    ICReg_NColorDif_Enable = 0xC9,  //N框色差算法使能
    ICReg_NColorDif_Mode,           //N框色差模式选择
    ICReg_NColorDif_Sensor,         //N框色差灵敏度
    ICReg_NColorDif_RGB,            //N框色差阈值颜色选择
    ICReg_NColorDif_Upper,          //N框色差阈值--上限
    ICReg_NColorDif_Lower,          //N框色差阈值--下限
    ICReg_NColorDif_Width,          //N框色差宽度设置
    ICReg_NColorDif_Height,         //N框色差高度设置
    ICReg_NColorDif_Threshold,      //N框色差算法阈值设置

    //hsv algo params
    ICReg_HSV_Enable = 0xD2,        //HSV算法使能
    ICReg_HSV_HUpper,               //HSV - H - 上限
    ICReg_HSV_HLower,               //HSV - H - 下限
    ICReg_HSV_SUpper,               //HSV - S - 上限
    ICReg_HSV_SLower,               //HSV - S - 下限
    ICReg_HSV_VUpper,               //HSV - V - 上限
    ICReg_HSV_VLower,               //HSV - V - 下限
    ICReg_HSV_Width,                //HSV_area_aixs_x
    ICReg_HSV_Height,               //HSV_area_aixs_y
    ICReg_HSV_Threhold,             //HSV_area_threshold


    //read only param
    ICReg_Firmware_Version = 0xE0,
    ICReg_Sensor_Type,
    ICReg_Sensor_OutMode,
    ICReg_Sensor_MaxFramerate,
    ICReg_Sensor_PixelSize,

    ICReg_Sensor_LineTime,
    ICReg_Sensor_WidthLimit,
    ICReg_Sensor_HeightLimit,
    ICReg_Read_DataLen,
    ICReg_Support_ImgFormt,

    ICReg_Support_PixFormt,
    ICReg_Support_TrigMode,
    ICReg_Support_ExposureMode
}KICRegister;


#endif // KICTYPEDEF_H
