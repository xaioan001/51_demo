/******************************************************************************
   本C文件里的各个子函数为了能阅读容易些，单条指令没加 大括号了
******************************************************************************/
#include "LCD_BASE.h"
#include "LCD_DISPLAY.h"
#include "lcdfont.h"
#include "STC8G_H_SPI.h"

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
//	u8 i;
//	for(i=0;i<8;i++)
//	{			  
//		LCD_SCL=0;
//		if(dat&0x80)
//		{
//		  LCD_SDA=1;			
//		}	
//		else
//		{
//		  LCD_SDA=0;			
//		}	
//		LCD_SCL=1;
//		dat<<=1;
//	}	
	
	SPDAT = dat;
	B_SPI_Busy = 1;
	while(B_SPI_Busy) ;
	
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC=0;//写命令
	LCD_Writ_Bus(dat);
	LCD_DC=1;//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/

void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{	
 if(USE_HORIZONTAL==3 || USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
}

/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/

void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);		
		}
	} 					  	    
}


/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_Address_Set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(color);
} 


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)
	{
		incx=1; //设置单步方向 	
	}
	else if (delta_x==0)
	{
		incx=0;//垂直线 	
	}
	else 
	{
		incx=-1;
		delta_x=-delta_x;
	}
	if(delta_y>0)
	{
		incy=1;	
	}
	else if (delta_y==0)
	{
		incy=0;//水平线	
	} 
	else 
	{
		incy=-1;
		delta_y=-delta_y;
	}
	if(delta_x>delta_y)
	{
		distance=delta_x; //选取基本增量坐标轴 	
	}
	else 
	{
		distance=delta_y;	
	}
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

/******************************************************************************
      函数说明：显示汉字串
      入口数据：x,y显示坐标
                *s 要显示的汉字串
                fc 字的颜色
                bc 字的背景色
                sizey 字号 可选 16 24 32
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	while(*s!=0)
	{
	  if(sizey==16)
		{
			LCD_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);		
		}
		else if(sizey==24)
		{
			LCD_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);		
		}
		else
		{
			return;		
		}
		s+=2;
		x+=sizey;
	}
}
/******************************************************************************
      函数说明：显示单个16x16汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j,m=0;
	u16 k;
	u16 HZnum;//汉字数目
	u16 TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//非叠加方式
					{
						if(tfont16[k].Msk[i]&(0x01<<j))
						{
							LCD_WR_DATA(fc);
						}
						else 
						{
							LCD_WR_DATA(bc);						
						}
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//叠加方式
					{
						if(tfont16[k].Msk[i]&(0x01<<j))
						{
							LCD_DrawPoint(x,y,fc);//画一个点						
						}
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 


/******************************************************************************
      函数说明：显示单个24x24汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;//汉字数目
	u16 TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	TypefaceNum=3*sizey;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//非叠加方式
					{
						if(tfont24[k].Msk[i]&(0x01<<j))
						{
							LCD_WR_DATA(fc);						
						}
						else 
						{
							LCD_WR_DATA(bc);						
						}
					}
					else//叠加方式
					{
						if(tfont24[k].Msk[i]&(0x01<<j))	
						{
							LCD_DrawPoint(x,y,fc);//画一个点						
						}
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
} 

			
/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 temp,sizex,t,m=0;
	u16 i,TypefaceNum;//一个字符所占字节大小
	u16 x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==16)
		{
			temp=ascii_1608[num][i];		 //调用8x16字体		
		}
		else if(sizey==24)
		{
			temp=ascii_2412[num][i];		 //调用12x24字体		
		}
		else 
		{
			return;		
		}
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))
				{
					LCD_WR_DATA(fc);				
				}
				else 
				{
					LCD_WR_DATA(bc);				
				}
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))
				{
					LCD_DrawPoint(x,y,fc);//画一个点				
				}
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/*****************************************************************************
      函数说明：汉字、字符串混合显示
      入口数据：x,y显示坐标
                *str 要显示的汉字、字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号大小，注意 此处函数的字符和汉字必须大小一致
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/	   		   
void Show_StringandChinese(u16 x,u16 y,u8 *str, u16 fc,u16 bc,u8 sizey,u8 mode)
{					
	u16 x0=x;							  	  
  u8 bHz=0;        //字符或者中文 
	while(*str!=0)    //数据未结束
	{ 
		if(!bHz)
		{
			if(*str>0x80)
			{
				bHz=1;     //中文 			
			}
			else         //字符
			{          
				if(*str==0x0D)     //换行符号
				{         
					y+=sizey;
					x=x0;
					str++; 
				}  
				else
				{
					LCD_ShowChar(x,y,*str,fc,bc,sizey,mode);
					x+=sizey/2;
				} 
			 str++; 	        
			}
		}
		else   //中文 
		{   
			bHz=0;  //有汉字库    
	    if(sizey==16) 
			{
				LCD_ShowChinese16x16(x,y,str,fc,bc,sizey,mode);			
			}
		  else if(sizey==24)
			{
				LCD_ShowChinese24x24(x,y,str,fc,bc,sizey,mode);			
			}
		  else 
			{
				return;			
			}
			str+=2; 
			x+=sizey;//下一个汉字偏移		
		}						 
	}   
}

/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result = 1;	 
	while(n--)
	{
		result*=m;	
	}
	return 
		result;	
}


/******************************************************************************
      函数说明：显示一位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
/*
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,temp1,sizex;
	u16 num1;
	sizex=sizey/2; 
	num1=num*10;  //小数点后一位，先乘出来得到整数
	for(t=0;t<len;t++)  
	{	
		if(num1 == 0)   // 数据是0时，显示 0，而不是 00.00
		{
			if(t <= len-1) 
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);			
			}
			if(t == len-1)
			{
				LCD_ShowChar(x+(t+1)*sizex,y,'0',fc,bc,sizey,0);			
			}
		}
		else  // 数据非0
		{
			temp = num1/mypow(10,len-t-1);  // 求商
		  temp1 = (num1/mypow(10,len-t-1))%10;  // 求余，得到每一位数字
			if(temp == 0 && ((len-2) > t))   // 得到的商是0（例：000.12，只显示最后三位有效数字 即：0.12）
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);			
			}
			else  // 得到的商非0（例：1.23）
			{
				if(t == (len-1))
				{
					LCD_ShowChar(x+(len-1)*sizex,y,'.',fc,bc,sizey,0); //显示小数点
					t++;
					len+=1;
				}
				LCD_ShowChar(x+t*sizex,y,temp1+48,fc,bc,sizey,0);  //显示数字			
			}
		}
	}
}
*/

/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/

void LCD_ShowFloatNum2(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,temp1,sizex;
	u16 num1;
	sizex=sizey/2; 
	num1=num*100;  //小数点后两位，先乘出来得到整数
	for(t=0;t<len;t++)  
	{	
		if(num1 == 0)   // 数据是0时，显示 0，而不是 00.00
		{
			if(t <= len-1) 
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);			
			}
			if(t == len-1)
			{
				LCD_ShowChar(x+(t+1)*sizex,y,'0',fc,bc,sizey,0);			
			}
		}
		else  // 数据非0
		{
			temp = num1/mypow(10,len-t-1);  // 求商
		  temp1 = (num1/mypow(10,len-t-1))%10;  // 求余，得到每一位数字
			if(temp == 0 && ((len-3) > t))   // 得到的商是0（例：000.12，只显示最后三位有效数字 即：0.12）
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
			else  // 得到的商非0（例：1.23）
			{
				if(t == (len-2))
				{
					LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0); //显示小数点
					t++;
					len+=1;
				}
				LCD_ShowChar(x+t*sizex,y,temp1+48,fc,bc,sizey,0);  //显示数字			
			}
		}
	}
}


/******************************************************************************
      函数说明：显示三位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloatNum3(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,temp1,sizex;
	u16 num1;
	sizex=sizey/2; 
	num1=num*1000;  //小数点后三位，先乘出来得到整数
	for(t=0;t<len;t++)  
	{	
		if(num1 == 0)   // 数据是0时，显示 0，而不是 00.000
		{
			if(t <= len-1) 
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);			
			}
			if(t == len-1)
			{
				LCD_ShowChar(x+(t+1)*sizex,y,'0',fc,bc,sizey,0);			
			}
		}
		else  // 数据非0
		{
			temp = num1/mypow(10,len-t-1);  // 求商
		  temp1 = (num1/mypow(10,len-t-1))%10;  // 求余，得到每一位数字
			if(temp == 0 && ((len-4) > t))   // 得到的商是0（例：00.123，只显示最后四位有效数字 即：0.123）
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
			else  // 得到的商非0（例：1.234）
			{
				if(t == (len-3))
				{
					LCD_ShowChar(x+(len-3)*sizex,y,'.',fc,bc,sizey,0); //显示小数点
					t++;
					len+=1;
				}
				LCD_ShowChar(x+t*sizex,y,temp1+48,fc,bc,sizey,0);  //显示数字			
			}
		}
	}
}


/******************************************************************************
      函数说明：显示16位真彩图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组    
      返回值：  无
******************************************************************************/

void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[])
{
	u16 i,j;
	u32 k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}			
}


/******************************************************************************
      函数说明：显示单色图片
      入口数据：x,y起点坐标
                length 图片长度,必须是8的倍数
                width  图片宽度
                pic[]  图片数组  
                fc 字的颜色
                bc 字的背景色
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/

void LCD_ShowPictureBW(u16 x,u16 y,u16 length,u16 width,const u8 pic[],u16 fc,u16 bc,u8 mode)
{
	u8 temp,sizex,t;
	u16 i,j;
	u16 x0=x;
	sizex=length/8;
	LCD_Address_Set(x,y,x+length-1,y+width-1);  //设置显示区域，必须和图片大小一致
	for(i=0;i<width;i++)  // 逐行显示
	{ 
		for(j=0;j<sizex;j++)  // 显示行里的数据
		{
			temp=pic[j+i*sizex];		
			for(t=0;t<8;t++)
			{
				if(!mode)//非叠加模式
				{
					if(temp&(0x01<<t))
					{
						LCD_WR_DATA(fc);					
					}
					else 
					{
						LCD_WR_DATA(bc);					
					}
				}
				else//叠加模式
				{
					if(temp&(0x01<<t))
					{
						LCD_DrawPoint(x,y,fc);//画一个点					
					}
					x++;
					if((x-x0)==sizex)
					{
						x=x0;
						y++;
						break;
					}
				}
			}
		}
	}   	 	  
}

/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/

void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}
			else 
			{
				enshow=1; 			
			}	 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      函数说明：全屏黑屏初始化显示，高刷新率
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
      返回值：  无
******************************************************************************/
void LCD_Fill_Black(u16 xsta,u16 ysta,u16 xend,u16 yend)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{		  
			 // 一个数据2个字节
			LCD_Writ_Bus(0x00);
			LCD_Writ_Bus(0x00);
		}
	}	
}



