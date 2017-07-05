#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>

//���� Ȱ������ ����
#define DAYTIME_ACTCOUNT 3

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursorOff(void)
{
	CONSOLE_CURSOR_INFO Information;
	Information.dwSize = 1;
	Information.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
}

void bfclear()
{
	while (getchar() != '\n');
}

void cursorOn(void)
{
	CONSOLE_CURSOR_INFO Information;

	Information.dwSize = 20;
	Information.bVisible = TRUE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Information);
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
				printf("������ %d�� ã�Ҵ�!", rslt);
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
	int srchbody, rqpoint = 0;
	if (base->curlife > 0)
	{
		int i;
		while (1)
		{
			printf("�İ��� �ο� ����?");
			bfclear();
			scanf("%d", &srchbody);
			if ((srchbody < base->curlife) && (srchbody > 0)) break;
			else printf("�İ��ο��� �ּ� 1�� �̻��� �Ǿ�� �ϸ�, ������ �Ѹ� �̻��� ���ƾ� �մϴ�.\n");
		}
		int restemp;
		while (1)
		{
			printf("�ڿ��� ����Ͽ� ������ ����� �� ���� �� �������� �𸨴ϴ�.\n1. ����\n2.��\n0. ������� �ʴ´�.");
			bfclear();
			char temp = getchar();
			switch (temp)
			{
			case '1':
				for (i = 0; i < 20; i++) { if (!strcmp(base->inven[i].name, "����")) break; };
				printf("%s:�� �� ����Ͻðڽ��ϱ�?", base->inven[i].name);
				scanf("%d", &restemp);
				if (restemp < base->inven[i].cur_cnt&&restemp>0)
				{
					base->inven[i].cur_cnt -= restemp;
					rqpoint += restemp * 1;
					printf("%s %d �� ����Ͽ���.", base->inven[i].name, restemp);
				}
				else printf("������ �ʹ� ũ�ų� �۽��ϴ�.");
				break;
			case '2':
				for (i = 0; i < 20; i++) { if (!strcmp(base->inven[i].name, "��")) break; };
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
			bfclear();
			char lastpic = getchar();
			if (lastpic == 'n' || lastpic == 'N') break;
		}
		//0���� ���� ���� �߻�. �����ääää�
		int rslt = rand() % ((srchbody / 5) + (rqpoint == 0 ? 0 : rand() % (rqpoint / 5))) == 0 ? 1 : (srchbody / 5) + (rqpoint == 0 ? 0 : rand() % (rqpoint / 5));
		if (rslt + base->curlife < base->maxlife)
		{
			base->curlife += rslt;
			printf("%d���� ����� ���ϴµ� �����ߴ�\n", rslt);
		}
		else
		{
			int overbody = ((base->curlife + rslt) - base->maxlife);
			base->curlife += rslt - overbody;
			printf("%d���� ����� ����������, �������� ������ ���ڶ� %d���� ����鸸 �������� ���Դ�.\n", rslt, rslt - overbody);
		}
	}
	else printf("�İߺ��� ����� �����ϴ�.\n");
}
void defsrchchk(leader* user)
{
	user->base->def = 0;
	user->base->maxlife = 10;
	for (int j = 0; j < 20; j++)
	{
		user->base->inven[j].stackmax = 30;
	}
	for (int i = 0; i < 20; i++)
	{
		switch (user->base->roomspace[i].roomtype)
		{
		case 1:
			user->base->def += user->base->roomspace[i].aply_bonus;
			break;
		case 2:
			user->base->maxlife += user->base->roomspace[i].aply_bonus;
			break;
		case 3:
			for (int j = 0; j < 20; j++)
			{
				user->base->inven[j].stackmax += user->base->roomspace[i].aply_bonus;
			}
			break;
		default:
			break;
		}
	}
}

void daytime(leader* user)
{
	int actcnt = DAYTIME_ACTCOUNT;
	printf("\t\t%s�� ��δ�\n", user->username);
	printf("------------------------------------------------\n\n");
	printf("                ������ �� : %d/%d\n\n", user->base->maxlife, user->base->curlife);
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
			defsrchchk(user);
			break;
		case 'f': case 'F':
			if (finditem(user->base) != 0) actcnt--;
			break;
		case 's': case 'S':
			rescuetribe(user->base); actcnt--;
			break;
		default:
			printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���\n");
			break;
		}
	}
}

void nighttime(leader* user, int level)
{
	printf("������.."); Sleep(1000); printf("����.."); Sleep(800);
	printf("����"); Sleep(500); printf("."); Sleep(300); printf("."); Sleep(300); printf("."); Sleep(300); puts("");
	printf("���� �Ǿ���. ����κ��� ��Ƴ��ƾ� �Ѵ�..\n");
	int zombiemax = ((level*level) / 2) + 3;
	int zombiemin = zombiemax / 2;
	int curwave = (rand() % (zombiemax - zombiemin)) + zombiemin;
	printf("���� %d������ �������� ���� �ִ�..\n", curwave);
	Sleep(1000);
	if (curwave - user->base->def > user->base->curlife)
	{
		printf("������ ������� ������");
		if ((curwave - user->base->def) - user->base->curlife < 3)
		{
			printf(" �� ���Ƴ��� �� ������, �Ҽ��� ������� �ٸ�����Ʈ�� �Ѿ�Դ�!\n");
			if (((rand() % 6) + 1) < 3)
			{
				int hidepeople = (user->base->curlife / 10) + 1;
				printf("�Ƽ������� �� ��δ翡��, %d���� ������ ��� ���߳��� �� �����ߴ�..\n", hidepeople);
				user->base->curlife = hidepeople;
			}
			else
			{
				printf("������� ������ �Ƽ������� �� ��δ��� �Ӽ���å���� ������ �ұ��� �Ǿ���..\n");
				user->base->curlife = 0;
			}
		}
		else
		{
			printf("���Ƴ���� �Ұ����ߴ�..\n");
			user->base->curlife = 0;
		}
	}
	else
	{
		int deathpeople = 0;
		for (int i = (curwave - user->base->def); i > 0; i--)
		{
			if ((rand() % 100) < 33)
			{
				user->base->curlife--;
				deathpeople++;
			}
		}
		if (deathpeople == 0) printf("�̹� ���� ������ ��������. ���ེ���� ����ڴ� �ƹ��� ������.\n");
		else
		{
			printf("�̹� ���� ����κ��� ��Ƴ��Ҵ�.. %d���� ����� ����� ������ ������ ������.\n", deathpeople);
		}
	}
}

void logo()
{
	cursorOff();
	int x,y;
	while (1)
	{
		x = (rand() % 4) + 3, y = rand() % 4;
		gotoxy(x, y); puts("          ��       ��");
		gotoxy(x, y+1); puts("        ��  ��     ��                                                ��              ");
		gotoxy(x, y+2); puts("       ��    ��    ����                               ��           ��                                   �������    ��");
		gotoxy(x, y+3); puts("      ��      ��   ��                     ��            ��           ������                 ��                      ��    ��");
		gotoxy(x, y+4); puts("                   ��             ��      ��            ��           ��            ��       ��                      ��    ��");
		gotoxy(x, y+5); puts("                               ��    ��   �ƾƾ�        ����������   ��         ��    ��    �ƾƾ�        �������    �����");
		gotoxy(x, y+6); puts("           �����            ��    ��   ��                         ��         ��    ��    ��            ��              ��");
		gotoxy(x, y+7); puts("                 ��             �ƾƾ�    ��              ������������           �ƾƾ�     ��            ��              ��");
		gotoxy(x, y+8); puts("           �����                       ��              ��        ��                      ��            �������    ��");
		gotoxy(x, y+9); puts("           ��                                             ������������");
		gotoxy(x, y+10); puts("           �����");                                            
		gotoxy(x, y+14); puts("                              ��           ������������   ��        ����������    �� ��           ""                        ""   !!!");
		gotoxy(x, y+15); puts("              ��������  ��                    ��    ��        ��            �� ��         ""   ������������    ��   ""     !!!");
		gotoxy(x, y+16); puts("              ��              ��                   ��     ��        ��������  ������ ��                      ��    ��        !!!");
		gotoxy(x, y+17); puts("              ��              ��                 ��       ��        ��            �� ��                      ��    ��        !!!");
		gotoxy(x, y+18); puts("              ��              ��               ��  ��     ��        ����������    �� ��            ������������    ��        !!!");
		gotoxy(x, y+19); puts("              ��              ��             ��     ��    ��                                       ��              ��        !!!");
		gotoxy(x, y+20); puts("              ��������  ��           ��        ��   ��             ������������              ��              ��");
		gotoxy(x, y+21); puts("                              ��                                                    ��             ������������    ��        !!!");
		gotoxy(x, y+22); puts("                                                                                    ��");
		puts(""); puts("");
		puts("						�ƹ�Ű�� ������ ���� ����");
		Sleep(1000);
		system("cls");
		if (kbhit()) 
		{
			cursorOn();
			break; 
		}
	}
}

void gameover()
{
	puts("		      !,    ");
	puts("	             ,:");
	puts("	          = #**: .     ");
	puts("	         !=.**.:~#*- ");
	puts("	             *.    ");
	puts("	             ==     ");
	puts("	            !;~;    ");
	puts("	           .* ~-$    ");
	puts("	          ~:!  *: -     ");
	puts("	        ~; .    ., -@  ");
	puts("	        ;.~      :!$*   ");
	puts("	        ;       !  ~@  ");
	puts("	        !          ~# ");
	puts("	        ;          ~$");
	puts("	        -  -.      ~# ");
	puts("	        !=;.    $. *@ ");
	puts("	        ;..........-$  ");
	puts("	      -------~-;;;;~,,,;");
	puts("	     ======;;*####@#=*:; : ");
	puts(""); puts("");
	puts(" ::::::::      :::     ::::    ::::  :::::::::: ");
	puts(":+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:        ");
	puts("+:+         +:+   +:+  +:+ +:+:+ +:+ +:+        ");
	puts(":#:        +#++:++#++: +#+  +:+  +#+ +#++:++#   ");
	puts("+#+   +#+# +#+     +#+ +#+       +#+ +#+        ");
	puts("#+#    #+# #+#     #+# #+#       #+# #+#        ");
	puts(" ########  ###     ### ###       ### ########## ");
	puts(" ::::::::  :::     ::: :::::::::::   :::::::::  ");
	puts(":+:    :+: :+:     :+: :+:           :+:    :+: ");
	puts("+:+    +:+ +:+     +:+ +:+           +:+    +:+ ");
	puts("+#+    +:+ +#+     +:+ +#++:++:+#    +#++:++#:  ");
	puts("+#+    +#+  +#+   +#+  +#+           +#+    +#+ ");
	puts("#+#    #+#   #+#+#+#   #+#           #+#    #+# ");
	puts(" ########      ###     ###########   ###    ### ");
}


void main()
{
	leader realuser;
	shelter base;
	int liveday;
	while (1)
	{
		liveday = 0;
		base.maxlife = 10;
		base.curlife = base.maxlife;
		realuser.base = &base;
		strcpy(realuser.base->inven[0].name, "����");
		strcpy(realuser.base->inven[1].name, "��");
		realuser.base->inven[0].cur_cnt = 30;
		realuser.base->inven[0].stackmax = 30;

		logo();

		printf("����� �̸��� �����Դϱ�? (���� 20���� �ѱ� 10���� �̳���)");
		scanf("%s", realuser.username);


		for (int i = 0; i < 20; i++)
			realuser.base->roomspace[i].roomtype = 0;
		while (1)
		{
			daytime(&realuser);
			nighttime(&realuser, liveday);
			if (realuser.base->curlife <= 0)
			{
				gameover();
				puts("===========================================");
				printf("\t��ΰ� �׾����ϴ�. ��Ƴ��� ����� �����ϴ�.\n");
				break;
			}
			liveday++;
		}
		printf("\t%d�ϰ� ��Ƴ��Ҵ�.");
		printf("���ο� ������ �����Ͻðڽ��ϱ�? (Y�� �Է��� �� ���� ����)");
		bfclear();
		char resel = getchar();
		if (!(resel == 'y' || resel == 'Y')) break;
		else system("cls");
	}
}