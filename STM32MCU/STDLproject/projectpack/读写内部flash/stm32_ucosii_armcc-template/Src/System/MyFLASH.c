#include "stm32f10x.h"

/**
 * @brief 从指定地址读取一个32位字（Word）
 * @param Address 读地址
 * @return 读取到的32位数据
 */
uint32_t MyFLASH_ReadWord(uint32_t Address)
{
    return *(__IO uint32_t*)(Address);
}

/**
 * @brief 从指定地址读取一个16位半字（Half-Word）
 * @param Address 读地址
 * @return 读取到的16位数据
 */
uint16_t MyFLASH_ReadHalfWord(uint32_t Address)
{
    return *(__IO uint16_t*)(Address);
}

/**
 * @brief 从指定地址读取一个字节（Byte）
 * @param Address 读地址
 * @return 读取到的8位数据
 */
uint8_t MyFLASH_ReadByte(uint32_t Address)
{
    return *(__IO uint8_t*)(Address);
}

/**
 * @brief 擦除 Flash 中的所有页
 * @note 该操作将清除整个 Flash 区域，执行耗时较长。
 */
void MyFLASH_EraseAllPages(void)
{
    FLASH_Unlock();//解锁
    FLASH_EraseAllPages();//擦除所有页
    FLASH_Lock();//上锁
}

/**
 * @brief 擦除指定页的FLASH
 * @param Page_Address 要擦除的页地址
 * @retval None
 */
void MyFLASH_ErasePage(uint32_t Page_Address)
{
    FLASH_Unlock();//解锁
    FLASH_ErasePage(Page_Address);//擦除页
    FLASH_Lock();//上锁
}

/**
 * @brief 向指定地址写入一个32位字（Word）
 * @param Address 写入地址
 * @param Data 要写入的32位数据
 * @retval None
 */
void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Unlock();//解锁
    FLASH_ProgramWord(Address, Data);//写入数据
    FLASH_Lock();//上锁
}

void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
    FLASH_Unlock();//解锁
    FLASH_ProgramHalfWord(Address, Data);//写入数据
    FLASH_Lock();//上锁
}