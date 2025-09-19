/******************************************************************************
   ��C�ļ���ĸ����Ӻ���Ϊ�����Ķ�����Щ������ָ��û�� ��������
******************************************************************************/
#include "LCD_BASE.h"
#include "LCD_DISPLAY.h"
#include "lcdfont.h"
#include "STC8G_H_SPI.h"

/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
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
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC=0;//д����
	LCD_Writ_Bus(dat);
	LCD_DC=1;//д����
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/

void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{	
 if(USE_HORIZONTAL==3 || USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
}

/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
								color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/

void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);		
		}
	} 					  	    
}


/******************************************************************************
      ����˵������ָ��λ�û���
      ������ݣ�x,y ��������
                color �����ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_Address_Set(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA(color);
} 


/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   �ߵ���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)
	{
		incx=1; //���õ������� 	
	}
	else if (delta_x==0)
	{
		incx=0;//��ֱ�� 	
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
		incy=0;//ˮƽ��	
	} 
	else 
	{
		incy=-1;
		delta_y=-delta_y;
	}
	if(delta_x>delta_y)
	{
		distance=delta_x; //ѡȡ�������������� 	
	}
	else 
	{
		distance=delta_y;	
	}
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//����
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
      ����˵������ʾ���ִ�
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ��ִ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ� ��ѡ 16 24 32
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
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
      ����˵������ʾ����16x16����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j,m=0;
	u16 k;
	u16 HZnum;//������Ŀ
	u16 TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//�ǵ��ӷ�ʽ
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
					else//���ӷ�ʽ
					{
						if(tfont16[k].Msk[i]&(0x01<<j))
						{
							LCD_DrawPoint(x,y,fc);//��һ����						
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
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
} 


/******************************************************************************
      ����˵������ʾ����24x24����
      ������ݣ�x,y��ʾ����
                *s Ҫ��ʾ�ĺ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 i,j;
	u16 k;
	u16 HZnum;//������Ŀ
	u16 TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
	TypefaceNum=3*sizey;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//ͳ�ƺ�����Ŀ
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//�ǵ��ӷ�ʽ
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
					else//���ӷ�ʽ
					{
						if(tfont24[k].Msk[i]&(0x01<<j))	
						{
							LCD_DrawPoint(x,y,fc);//��һ����						
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
		continue;  //���ҵ���Ӧ�����ֿ������˳�����ֹ��������ظ�ȡģ����Ӱ��
	}
} 

			
/******************************************************************************
      ����˵������ʾ�����ַ�
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ���ַ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode)
{
	u8 temp,sizex,t,m=0;
	u16 i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	u16 x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //���ù��λ�� 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==16)
		{
			temp=ascii_1608[num][i];		 //����8x16����		
		}
		else if(sizey==24)
		{
			temp=ascii_2412[num][i];		 //����12x24����		
		}
		else 
		{
			return;		
		}
		for(t=0;t<8;t++)
		{
			if(!mode)//�ǵ���ģʽ
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
			else//����ģʽ
			{
				if(temp&(0x01<<t))
				{
					LCD_DrawPoint(x,y,fc);//��һ����				
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
      ����˵������ʾ�ַ���
      ������ݣ�x,y��ʾ����
                *p Ҫ��ʾ���ַ���
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
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
      ����˵�������֡��ַ��������ʾ
      ������ݣ�x,y��ʾ����
                *str Ҫ��ʾ�ĺ��֡��ַ�
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺŴ�С��ע�� �˴��������ַ��ͺ��ֱ����Сһ��
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/	   		   
void Show_StringandChinese(u16 x,u16 y,u8 *str, u16 fc,u16 bc,u8 sizey,u8 mode)
{					
	u16 x0=x;							  	  
  u8 bHz=0;        //�ַ��������� 
	while(*str!=0)    //����δ����
	{ 
		if(!bHz)
		{
			if(*str>0x80)
			{
				bHz=1;     //���� 			
			}
			else         //�ַ�
			{          
				if(*str==0x0D)     //���з���
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
		else   //���� 
		{   
			bHz=0;  //�к��ֿ�    
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
			x+=sizey;//��һ������ƫ��		
		}						 
	}   
}

/******************************************************************************
      ����˵������ʾ����
      ������ݣ�m������nָ��
      ����ֵ��  ��
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
      ����˵������ʾһλС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
/*
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,temp1,sizex;
	u16 num1;
	sizex=sizey/2; 
	num1=num*10;  //С�����һλ���ȳ˳����õ�����
	for(t=0;t<len;t++)  
	{	
		if(num1 == 0)   // ������0ʱ����ʾ 0�������� 00.00
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
		else  // ���ݷ�0
		{
			temp = num1/mypow(10,len-t-1);  // ����
		  temp1 = (num1/mypow(10,len-t-1))%10;  // ���࣬�õ�ÿһλ����
			if(temp == 0 && ((len-2) > t))   // �õ�������0������000.12��ֻ��ʾ�����λ��Ч���� ����0.12��
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);			
			}
			else  // �õ����̷�0������1.23��
			{
				if(t == (len-1))
				{
					LCD_ShowChar(x+(len-1)*sizex,y,'.',fc,bc,sizey,0); //��ʾС����
					t++;
					len+=1;
				}
				LCD_ShowChar(x+t*sizex,y,temp1+48,fc,bc,sizey,0);  //��ʾ����			
			}
		}
	}
}
*/

/******************************************************************************
      ����˵������ʾ��λС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/

void LCD_ShowFloatNum2(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,temp1,sizex;
	u16 num1;
	sizex=sizey/2; 
	num1=num*100;  //С�������λ���ȳ˳����õ�����
	for(t=0;t<len;t++)  
	{	
		if(num1 == 0)   // ������0ʱ����ʾ 0�������� 00.00
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
		else  // ���ݷ�0
		{
			temp = num1/mypow(10,len-t-1);  // ����
		  temp1 = (num1/mypow(10,len-t-1))%10;  // ���࣬�õ�ÿһλ����
			if(temp == 0 && ((len-3) > t))   // �õ�������0������000.12��ֻ��ʾ�����λ��Ч���� ����0.12��
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
			else  // �õ����̷�0������1.23��
			{
				if(t == (len-2))
				{
					LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0); //��ʾС����
					t++;
					len+=1;
				}
				LCD_ShowChar(x+t*sizex,y,temp1+48,fc,bc,sizey,0);  //��ʾ����			
			}
		}
	}
}


/******************************************************************************
      ����˵������ʾ��λС������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾС������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
******************************************************************************/
void LCD_ShowFloatNum3(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,temp1,sizex;
	u16 num1;
	sizex=sizey/2; 
	num1=num*1000;  //С�������λ���ȳ˳����õ�����
	for(t=0;t<len;t++)  
	{	
		if(num1 == 0)   // ������0ʱ����ʾ 0�������� 00.000
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
		else  // ���ݷ�0
		{
			temp = num1/mypow(10,len-t-1);  // ����
		  temp1 = (num1/mypow(10,len-t-1))%10;  // ���࣬�õ�ÿһλ����
			if(temp == 0 && ((len-4) > t))   // �õ�������0������00.123��ֻ��ʾ�����λ��Ч���� ����0.123��
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
			else  // �õ����̷�0������1.234��
			{
				if(t == (len-3))
				{
					LCD_ShowChar(x+(len-3)*sizex,y,'.',fc,bc,sizey,0); //��ʾС����
					t++;
					len+=1;
				}
				LCD_ShowChar(x+t*sizex,y,temp1+48,fc,bc,sizey,0);  //��ʾ����			
			}
		}
	}
}


/******************************************************************************
      ����˵������ʾ16λ���ͼƬ
      ������ݣ�x,y�������
                length ͼƬ����
                width  ͼƬ���
                pic[]  ͼƬ����    
      ����ֵ��  ��
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
      ����˵������ʾ��ɫͼƬ
      ������ݣ�x,y�������
                length ͼƬ����,������8�ı���
                width  ͼƬ���
                pic[]  ͼƬ����  
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                mode:  0�ǵ���ģʽ  1����ģʽ
      ����ֵ��  ��
******************************************************************************/

void LCD_ShowPictureBW(u16 x,u16 y,u16 length,u16 width,const u8 pic[],u16 fc,u16 bc,u8 mode)
{
	u8 temp,sizex,t;
	u16 i,j;
	u16 x0=x;
	sizex=length/8;
	LCD_Address_Set(x,y,x+length-1,y+width-1);  //������ʾ���򣬱����ͼƬ��Сһ��
	for(i=0;i<width;i++)  // ������ʾ
	{ 
		for(j=0;j<sizex;j++)  // ��ʾ���������
		{
			temp=pic[j+i*sizex];		
			for(t=0;t<8;t++)
			{
				if(!mode)//�ǵ���ģʽ
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
				else//����ģʽ
				{
					if(temp&(0x01<<t))
					{
						LCD_DrawPoint(x,y,fc);//��һ����					
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
      ����˵������ʾ��������
      ������ݣ�x,y��ʾ����
                num Ҫ��ʾ��������
                len Ҫ��ʾ��λ��
                fc �ֵ���ɫ
                bc �ֵı���ɫ
                sizey �ֺ�
      ����ֵ��  ��
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
      ����˵����ȫ��������ʼ����ʾ����ˢ����
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill_Black(u16 xsta,u16 ysta,u16 xend,u16 yend)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{		  
			 // һ������2���ֽ�
			LCD_Writ_Bus(0x00);
			LCD_Writ_Bus(0x00);
		}
	}	
}



