#include<function.h>

int te_1,te_2;
uchar tc_data;

void loopctrl()
{
    int val,data_inc;
    //long temp;
    float t;
    val=Tset;		                  //�¶�����ֵ��չ1��
    if(Tm<val)	                  //��ǰ�¶�С���趨�¶�,���´���
    {	
        t=val-Tm;		              //����Ŀ���²�
        if(t>tvu)	                //Ŀ���²���ڷ�ֵ�Ĵ���
        {
            hold=0;		            //����¶ȱ��ֿ��Ʊ�־
            tc_data=255;	        //ǿ��DAC����Ϊ255
            CS2=tc_data;          //ˢ��DAC��������
        }
				else			//Ŀ���²�С�ڵ��ڷ�ֵ�Ĵ���
				{
					if(hold==0)		//���ν����¶ȱ��ֿ���״̬�Ĵ���
					{
							if(val>=t_room)   tc_data=dbasa;         //Ŀ���¶ȴ��ڵ������³�ֵ
							else		          tc_data=dbasb;         //Ŀ���¶�С�����µĳ�ֵ
							hold=1;		                               //��λ�¶ȱ��ֿ��Ʊ�־
					}		
					data_inc=2.0*(t-te_1)+0.1*t+1.0*(t-2*te_1+te_2);    //PID������������
					tc_data=tc_data+data_inc;	                          //����DAC��������
					if(tc_data+5>255)  CS2=255;		                      //ˢ��DAC��������
					else               CS2=tc_data+5;
				}
		}
    else				//��ǰ�¶ȴ��ڵ����趨�¶�,���´���
    {
        t=Tm-val;			//����Ŀ���²�
        if(t>tvd)			//Ŀ���²���ڷ�ֵ�Ĵ���
        {
            hold=0;			  //����¶ȱ��ֿ��Ʊ�־
            tc_data=0;		//ǿ��DAC����Ϊ0
            CS2=tc_data;	//ˢ��DAC��������
        }
        else				//Ŀ���²�С�ڵ��ڷ�ֵ�Ĵ���
        {
            if(hold==0)		//�¶ȱ��ֲ���
            {
								if(val>=t_room)   tc_data=dbasa;       //Ŀ���¶ȴ��ڵ������³�ֵ
								else	            tc_data=dbasb;       //Ŀ���¶�С�����³�ֵ
								hold=1;		                             //��λ�¶ȱ��ֿ��Ʊ�־
            }
            t=-t;	//Ŀ���²�ȡ��ֵ
            data_inc=2.0*(t-te_1)+0.1*t+1.0*(t-2*te_1+te_2);//PID������������
            tc_data=tc_data+data_inc;		                    //����DAC��������
					  if(tc_data+5>255)  CS2=255;		                      //ˢ��DAC��������
					  else               CS2=tc_data+5;
        }
    }
    te_2=te_1;
    te_1=t;
}

int dbasa,dbasb;
float tvu,tvd;

void calculate_pid()
{
	if(Tset>t_room) //��ǰ�¶�С���趨�¶�
	{
		//dbasa=(int)(40+(112/(100.0-t_room))*(Tset-t_room));  //156
		dbasa=(int)(Tset*256/100);
		if(dbasa>255)  dbasa=255;
		tc_data=dbasa;
	}
	else
	{
		dbasb=(int)(128-(112/(t_room+10))*(t_room-Tset));  //408
		if(dbasb<0)  dbasb=0;
	}
	tvu=(100-Tset)*0.07+1; 
	tvd=1+Tset*0.07;
	tc_data=dbasa;
}



void output_t_room()
{
	 CS2=(uchar)(t_room * 256) / 100;
} 