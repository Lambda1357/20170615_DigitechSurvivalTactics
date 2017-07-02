#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>

//���� Ȱ������ ����
#define DAYTIME_ACTCOUNT 3

void bfclear()
{
	while (getchar() != '\n');
}

struct shelt_room
{
	//0�� �̰Ǽ� 1�� ���ü�, 2�� �α��ü�, 3�� Ž���ü�, 4�� �����
	short roomtype = 0;
	short roomlv;
	int aply_bonus;
};
struct item
{
	char name[21];
	int cur_cnt;
	int stackmax;
};
struct shelter
{
	shelt_room roomspace[20];
	int def, srch;
	int maxlife;
	int curlife;
	item inven[20];
};
struct leader
{
	char username[21];

	shelter* base;
};

//�ǹ� ���׷��̵� �̱���
void buildroom(shelter* m_base)
{
	{
		bfclear();
		int roomnum;
		char temp;
		while (1)
		{
			printf("���� �ǹ� ���� ����");
			temp = getchar();
			bfclear();
			switch (temp)
			{
			case '1':
				while (1)
				{
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("������ %d�� �Ҹ��մϴ�. ����Ͻðڽ��ϱ�?(y,n)>>", useitemcnt);
							char temp = getchar();
							bfclear();
							if (temp = ('y' || 'Y'))
							{
								for (i = 0; m_base->inven[i].name != "����"; i++);
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 1,1,5 };
									break;
								}
								else printf("�ڿ��� ���ڶ��ϴ�.\n");
							}
						}
						else printf("�� �������� �̹� �ü��� �����մϴ�.\n");
					}
					else printf("��ȿ�� ���� �Է����ּ���.\n");
					printf("�׸��νðڽ��ϱ�? (�׸��η��� y �Է�)>>");
					if (getchar() == ('y' || 'Y')) break;
					else printf("��� �����մϴ�.");
				}
				break;
			case '2':
				while (1)
				{
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("������ %d�� �Ҹ��մϴ�. ����Ͻðڽ��ϱ�?(y,n)>>", useitemcnt);
							char temp = getchar();
							bfclear();
							if (temp = ('y' || 'Y'))
							{
								for (i = 0; m_base->inven[i].name != "����"; i++);
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 2,1,5 };
									break;
								}
								else printf("�ڿ��� ���ڶ��ϴ�.\n");
							}
						}
						else printf("�� �������� �̹� �ü��� �����մϴ�.\n");
					}
					else printf("��ȿ�� ���� �Է����ּ���.\n");
					printf("�׸��νðڽ��ϱ�? (�׸��η��� y �Է�)>>");
					if (getchar() == ('y' || 'Y')) break;
					else printf("��� �����մϴ�.");
				}
				break;
			case '3':
				while (1)
				{
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("������ %d�� �Ҹ��մϴ�. ����Ͻðڽ��ϱ�?(y,n)>>", useitemcnt);
							char temp = getchar();
							bfclear();
							if (temp = ('y' || 'Y'))
							{
								for (i = 0; m_base->inven[i].name != "����"; i++);
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 3,1,5 };
									break;
								}
								else printf("�ڿ��� ���ڶ��ϴ�.\n");
							}
						}
						else printf("�� �������� �̹� �ü��� �����մϴ�.\n");
					}
					else printf("��ȿ�� ���� �Է����ּ���.\n");
					printf("�׸��νðڽ��ϱ�? (�׸��η��� y �Է�)>>");
					if (getchar() == ('y' || 'Y')) break;
					else printf("��� �����մϴ�.");
				}
				break;
			default:
				continue;
			}
		}
	}
}

//
void finditem(shelter* base)
{
	printf("1.���� ã��,2.�� ã��");
	char temp = getchar();
	bfclear();
	switch (temp)
	{
		int srchbody;
	case '1':
		if (base->curlife > 0)
		{
			int i;
			while (1)
			{
				printf("�İ��� �ο� ����?");
				scanf("%d", &srchbody);
				if (srchbody < base->curlife&&srchbody>0) break;
				else printf("�İ��ο��� �ּ� 1�� �̻��� �Ǿ�� �ϸ�, ������ �Ѹ� �̻��� ���ƾ� �մϴ�.\n");
			}
			int rslt = rand() % (int)(srchbody * 1.5);
			for (i = 0; base->inven[i].name != "����"; i++) if (i>19) break;
			if (i < 20)
			{
				for (int j = 0; rslt <= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
			}
			else printf("����:�������� ������ġ�� ã�� �� �������ϴ�.\n");
		}
		else printf("�İߺ��� ����� �����ϴ�.\n");
		break;
	case '2':
		if (base->curlife > 0)
		{
			int i;
			while (1)
			{
				printf("�İ��� �ο� ����?");
				scanf("%d", &srchbody);
				if (srchbody < base->curlife&&srchbody>0) break;
				else printf("�İ��ο��� �ּ� 1�� �̻��� �Ǿ�� �ϸ�, ������ �Ѹ� �̻��� ���ƾ� �մϴ�.\n");
			}
			int rslt = rand() % (int)(srchbody * 1.5);
			for (i = 0; base->inven[i].name != "��"; i++) if(i>19) break;
			if (i < 20)
			{
				for (int j = 0; rslt <= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
			}
			else printf("����:�������� ������ġ�� ã�� �� �������ϴ�.\n");
		}
		else printf("�İߺ��� ����� �����ϴ�.\n");
		break;
	}
}

//
void rescuetribe(shelter* base)
{
	int srchbody,rqpoint;
	if (base->curlife > 0)
	{
		int i;
		while (1)
		{
			printf("�İ��� �ο� ����?");
			scanf("%d", &srchbody);
			if ((srchbody < base->curlife)&&(srchbody>0)) break;
			else printf("�İ��ο��� �ּ� 1�� �̻��� �Ǿ�� �ϸ�, ������ �Ѹ� �̻��� ���ƾ� �մϴ�.\n");
		}
		int restemp;
		while (1)
		{
			printf("�ڿ��� ����Ͽ� ������ ����� �� ���� �� �������� �𸨴ϴ�.\n1. ����\n2.��\n0. ������� �ʴ´�.");
			char temp = getchar();
			switch (temp)
			{
			case '1':
				for (i = 0; base->inven[i].name != "����"; i++) if (i>19) break;
				printf("%s:�� �� ����Ͻðڽ��ϱ�?");
				scanf("%d",&restemp);
				if (restemp < base->inven[i].cur_cnt&&restemp>0)
				{
					base->inven[i].cur_cnt -= restemp;
					rqpoint += restemp * 1;
					printf("%s %d �� ����Ͽ���.", base->inven[i].name, restemp);
				}
				else printf("������ �ʹ� ũ�ų� �۽��ϴ�.");
				break;
			case '2':
				for (i = 0; base->inven[i].name != "��"; i++) if (i>19) break;
				printf("%s:�� �� ����Ͻðڽ��ϱ�?");
				scanf("%d", &restemp);
				if (restemp < base->inven[i].cur_cnt&&restemp>0)
				{
					base->inven[i].cur_cnt -= restemp;
					rqpoint += (int)(restemp * 1.5);
					printf("%s %d �� ����Ͽ���.\n", base->inven[i].name, restemp);
				}
				else printf("������ �ʹ� ũ�ų� �۽��ϴ�.\n");
				break;
			default:
				printf("�߸� �Է��ϼ̽��ϴ�.\n");
				break;
			}
			printf("�ڿ��߰��� �� �ұ��? (���� �������� N �Է�)");
			char lastpic = getchar();
			if (lastpic == ('N'||'n')) break;
		}
		int rslt = rand() % (srchbody / 5) + (rqpoint == 0 ? 0 : rand() % (rqpoint / 5));
		if (rslt + base->curlife < base->maxlife)
		{
			base->curlife += rslt;
			printf("%d���� ����� ���ϴµ� �����ߴ�\n", rslt);
		}
		else
		{
			int overbody = ((base->curlife + rslt) - base->maxlife);
			base->curlife += rslt - overbody;
			printf("%d���� ����� ����������, �������� ������ ���ڶ� %d���� ����鸸 �������� ���Դ�.\n",rslt,rslt-overbody);
		}
	}
	else printf("�İߺ��� ����� �����ϴ�.\n");
}

void daytime(leader* user)
{
	bfclear();
	int actcnt = DAYTIME_ACTCOUNT;
	while (actcnt > 1)
	{
		printf("���̴�. ������?");
		char selchar = getchar();
		switch (selchar)
		{
		case 'r': case 'R':
			buildroom(user->base); actcnt--;
			break;
		case 'f': case 'F':
			finditem(user->base); actcnt--;
			break;
		case 's': case 'S':
			rescuetribe(user->base);
		default:
			printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���\n");
			break;
		}
	}
}


void main()
{
	leader realuser;
	shelter base;
	realuser.base = &base;
	strcpy(realuser.base->inven[0].name, "����");
	strcpy(realuser.base->inven[1].name, "��");
	printf("����� �̸��� �����Դϱ�? (���� 20���� �ѱ� 10���� �̳���)");
	scanf("%s", realuser.username);

	for (int i = 0; i < 20; i++)
		realuser.base->roomspace[i].roomtype = 0;
	while (1)
	{
		daytime(&realuser);
		break;
	}
}