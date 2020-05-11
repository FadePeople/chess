#pragma once				//�ϸ�ͷ�ļ�ֻ����һ��
typedef struct Point
{
	int i = 0;
	int j = 0;
}Point;

typedef struct Step
{
	Point From;              //���
	Point To;                //�յ�
	char chess;              //��������
}Step;

//��ֹ����ĥ��
class Grind
{
public:
	Step Steps[20];           //�߷�
	int Num = 0;              //�߷���
	void Clear();
	void Pop(int move[4], char chess);
	int IsGrind(int move[4], char chess);

private:

};

//�������� ѹ��
//�������� ����
//�������
//   move    �߷�
//   chess   ��ǰ����
//����ֵ  ��
void Grind::Pop(int move[4], char chess)
{
	if (chess != M_BOOM)
	{
		Steps[Num].From.i = move[0];           //��¼�ҷ�Ŀǰ�߷�
		Steps[Num].From.j = move[1];
		Steps[Num].To.i = move[2];
		Steps[Num].To.j = move[3];
		Steps[Num].chess = chess;
		Num++;
	}
}

//�������� ���
//�������� ���
//�������
//   ��
//����ֵ  ��
void Grind::Clear()
{
	Num = 0;
}

//��������
//�������� �ж��Ƿ���ĥ��
//�������
//  move    ���������ƶ�����
//  chess   ��ǰ��Ҫ�ƶ�������
//����ֵ  1 ȷʵ��ĥ�� 2 û����ĥ��
int Grind::IsGrind(int move[4], char chess)
{
	if (Num > 5)                                                                     //��5��ֵ���ϵĽ�������
	{
		int i;
		int n = 0;                                                                   //
		for (i = Num; i >= 2; i--)
		{
			if (Steps[i].From.i == Steps[i - 2].From.i&&                            //�Ӻ���ǰ��   ��¼ĥ�����
				Steps[i].From.j == Steps[i - 2].From.j&&
				Steps[i].To.i == Steps[i - 2].To.i&&
				Steps[i].To.j == Steps[i - 2].To.j&&
				Steps[i].chess == Steps[i - 2].chess&&
				Steps[i].chess == chess)
			{
				n++;                                                               //��¼ĥ����� ʵ��Ҫ��2
				continue;
			}
			else
				break;

		}
		if (n > 2)                                                                  //�ж�ĥ�峬��5����Ϊ��ĥ��
			if (Steps[Num].From.i == move[0] &&                                       //�ж���һ�����Ƿ���ѭ��
				Steps[Num].From.i == move[1] &&
				Steps[Num].To.i == move[2] &&
				Steps[Num].To.j == move[3])
				return 1;                                                           //��ȷʵ��ѭ��
		return 0;                                                                   //û��ѭ�������
	}
	return 0;                                                                       //��5��ֵ���µ�ֱ�ӷ���0
}

Grind NoGrind;
typedef struct Attribute              //����ֵ
{
	int IsFollowed = NOATTR;         //������  �з����Ի򼺷������Է��������ڸ��ʱ��λ��
	int IsTrace = NOATTR;            //����    ��������
	int Type = 0;                    //��������
}Attribute;

typedef struct Map                   //��ͼ
{
	char        chess = '0';         //��������
	Attribute   Attr;                //����
	int IsTouch = 0;                 //����ײ������
	int IsTouched = 0;               //��ײ����
}Map;
