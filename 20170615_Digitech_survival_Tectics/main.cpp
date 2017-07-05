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
char* roomtyper(int typecode)
{
	switch (typecode)
	{
	case 0:
		return "����";
		break;
	case 1:
		return "�ʼ�";
		break;
	case 2:
		return "�Ĵ�";
		break;
	case 3:
		return "Ž�����";
	case 4:
		return "â��";

	}
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

//�ǹ� ���׷��̵� �̱���, ���差 ���ȿ�� ����.
void buildroom(shelter* m_base)
{
	{
		/*���׶����� �ϴ� ����
		for (int i = 0; i < 5; i++)
			printf("%d��: %s\t%d��: %s\n%d��: %s\n%d��: %s", i + 1, roomtyper(m_base->roomspace[i].roomtype),
			i+5,roomtyper(m_base->roomspace[i+4].roomtype),i+10,roomtyper(m_base->roomspace[i+9].roomtype));*/
		int roomnum;
		char temp;
		printf("��δ� ���δ� �������� �д�. �ణ�� �ڿ��� �ִٸ� �պ� �� ���� �� ����...\n");
		while (1)
		{
			puts("-----------------------------------------");
			printf("1. ���� �����ϰ� �ʼҸ� ������. (���ü�)\n2. �Թ�� ���� ħ�븦 ����� ��Ȱ������ ������ (�α��ü�)\n3. ���縦 ����� ��ó�� �ѷ����� (Ž���ü�)\n0. �Ǽ��� �����Ѵ�.\n� �ü��� �����غ���? (���� �Է�)>>");
			bfclear();
			temp = getchar();
			switch (temp)
			{
			case '1':
				while (1)
				{
					printf("���ü��� �� �� ������ ����ðڽ��ϱ�?");
					bfclear();
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("������ %d�� �Ҹ��մϴ�. ����Ͻðڽ��ϱ�?(y,n)>>", useitemcnt);
							bfclear();
							char temp = getchar();
							if (temp == 'y' || temp == 'Y')
							{
								for (i = 0; i < 20; i++) { if (!strcmp(m_base->inven[i].name, "����")) break; };
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 1,1,5 };
									printf("�Ǽ��� ���������� ���ƽ��ϴ�.\n");
									break;
								}
								else printf("�ڿ��� ���ڶ��ϴ�.\n");
							}
						}
						else printf("�� �������� �̹� �ü��� �����մϴ�.\n");
					}
					else printf("��ȿ�� ���� �Է����ּ���.\n");
					printf("���ü� �Ǽ��� �׸��νðڽ��ϱ�? (�׸��η��� y �Է�)>>");
					bfclear();
					temp = getchar();
					if (temp == 'y' || temp == 'Y') break;
					else printf("��� �����մϴ�.\n");
				}
				break;
			case '2':
				while (1)
				{
					printf("�Ĵ��� �� �� ������ ����ðڽ��ϱ�?");
					bfclear();
					scanf("%d", &roomnum);
					if (roomnum > 0 && 20 >= roomnum)
					{
						int useitemcnt = 5;
						int i;
						if (m_base->roomspace[roomnum - 1].roomtype == 0)
						{
							printf("������ %d�� �Ҹ��մϴ�. ����Ͻðڽ��ϱ�?(y,n)>>", useitemcnt);
							bfclear();
							char temp = getchar();
							if (temp == 'y' || temp == 'Y')
							{
								for (i = 0; i < 20; i++) { if (!strcmp(m_base->inven[i].name, "����")) break; };
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 2,1,5 };
									printf("�Ǽ��� ���������� ���ƽ��ϴ�.\n");
									break;
								}
								else printf("�ڿ��� ���ڶ��ϴ�.\n");
							}
						}
						else printf("�� �������� �̹� �ü��� �����մϴ�.\n");
					}
					else printf("��ȿ�� ���� �Է����ּ���.\n");
					printf("�Ĵ� �Ǽ��� �׸��νðڽ��ϱ�? (�׸��η��� y �Է�)>>");
					bfclear();
					temp = getchar();
					if (temp == 'y' || temp == 'Y') break;
					else printf("��� �����մϴ�.\n");
				}
				break;
			case '3':
				while (1)
				{
					printf("Ž�������� �� �� ������ ����ðڽ��ϱ�?");
					bfclear();
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
							if (temp == 'y' || temp == 'Y')
							{
								for (i = 0; i < 20; i++) { if (!strcmp(m_base->inven[i].name, "����")) break; };
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 3,1,5 };
									printf("�Ǽ��� ���������� ���ƽ��ϴ�.\n");
									break;
								}
								else printf("�ڿ��� ���ڶ��ϴ�.\n");
							}
						}
						else printf("�� �������� �̹� �ü��� �����մϴ�.\n");
					}
					else printf("��ȿ�� ���� �Է����ּ���.\n");
					printf("Ž��ü� �Ǽ��� �׸��νðڽ��ϱ�? (�׸��η��� y �Է�)>>");
					bfclear();
					temp = getchar();
					if (temp == 'y' || temp == 'Y') break;
					else printf("��� �����մϴ�.\n");
				}
				break;
			case '0':
				break;
			default:
				printf("��ȿ�� ���� �Է��ϼ���\n");
			}
			printf("�Ǽ��۾��� �����ұ��? (�����Ѵٸ� y)>>");
			bfclear();
			char acter = getchar();
			if (acter == 'Y' || acter == 'y') break;
			else printf("�Ǽ��۾��� �ٽ� �����մϴ�.\n\n");
		}
	}
}

int finditem(shelter* base)
{
	int srchbody;
	printf("1.���� ã��,2.�� ã��");
	bfclear();
	char temp = getchar();
	switch (temp)
	{
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
			for (i = 0; strcmp(base->inven[i].name, "����") != 0; i++) if (i > 19) break;
			if (i < 20)
			{
				printf("������ %d�� ã�Ҵ�!",rslt);
				for (int j = 0; rslt >= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
				printf("\t���� ���� %d��", base->inven[i].cur_cnt);
				if (rslt != 0) printf("������ ���ڶ� %d���� �ڿ��� ���������ϴ�.",rslt);
				printf("\n");
				return 1;
			}
			else { printf("����:�������� ������ġ�� ã�� �� �������ϴ�.\n"); return 0; }
		}
		else { printf("�İߺ��� ����� �����ϴ�.\n"); return 0; }
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
			for (i = 0; strcmp(base->inven[i].name, "��") != 0; i++) if (i > 19) break;
			if (i < 20)
			{
				printf("���� %d�� ã�Ҵ�!", rslt);
				for (int j = 0; rslt >= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
				printf("\t���� ���� %d��", base->inven[i].cur_cnt);
				if (rslt != 0) printf("������ ���ڶ� %d���� �ڿ��� ���������ϴ�.", rslt);
				printf("\n");
				return 1;
			}
			else { printf("����:�������� ������ġ�� ã�� �� �������ϴ�.\n"); return 0; }
		}
		else { printf("�İߺ��� ����� �����ϴ�.\n"); return 0; }
		break;
	default:
		printf("�Է¿��� ������ �־����ϴ�.\n");
		return 0;
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
	int actcnt = DAYTIME_ACTCOUNT;
	printf("\t\t%s�� ��δ�\n", user->username);
	printf("------------------------------------------------\n\n");
	printf("                ������ �� : %d\n\n", user->base->curlife);
	printf("------------------------------------------------\n\n");

	printf("������ �� �ð��̴�. �ƹ����� ������� Ȱ���� �پ�� �� ����.\n");
	while (actcnt > 1)
	{
		printf("������ �ұ�?\n>> ��δ��� �ü��� �Ǽ����� (R)\n>> �ڿ��� ã���� ������ (F)\n>> �������� ����� ������  (S)\n\n���ĺ� �Է�>>");
		bfclear();
		char selchar = getchar();
		switch (selchar)
		{
		case 'r': case 'R':
			buildroom(user->base); actcnt--;
			break;
		case 'f': case 'F':
			if (finditem(user->base) != 0) actcnt--;
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

	base.maxlife = 10;
	base.curlife = base.maxlife;
	realuser.base = &base;
	strcpy(realuser.base->inven[0].name, "����");
	strcpy(realuser.base->inven[1].name, "��");
	realuser.base->inven[0].cur_cnt = 30;
	realuser.base->inven[0].stackmax = 30;

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