#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>

//낮의 활동갯수 정의
#define DAYTIME_ACTCOUNT 3

void bfclear()
{
	while (getchar() != '\n');
}

struct shelt_room
{
	//0은 미건설 1은 방어시설, 2는 인구시설, 3은 탐색시설, 4는 저장고
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

//건물 업그레이드 미구현
void buildroom(shelter* m_base)
{
	{
		bfclear();
		int roomnum;
		char temp;
		while (1)
		{
			printf("지을 건물 유형 선택");
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
							printf("나무를 %d개 소모합니다. 계속하시겠습니까?(y,n)>>", useitemcnt);
							char temp = getchar();
							bfclear();
							if (temp = ('y' || 'Y'))
							{
								for (i = 0; m_base->inven[i].name != "나무"; i++);
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 1,1,5 };
									break;
								}
								else printf("자원이 모자랍니다.\n");
							}
						}
						else printf("그 공간에는 이미 시설이 존재합니다.\n");
					}
					else printf("유효한 값을 입력해주세요.\n");
					printf("그만두시겠습니까? (그만두려면 y 입력)>>");
					if (getchar() == ('y' || 'Y')) break;
					else printf("계속 진행합니다.");
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
							printf("나무를 %d개 소모합니다. 계속하시겠습니까?(y,n)>>", useitemcnt);
							char temp = getchar();
							bfclear();
							if (temp = ('y' || 'Y'))
							{
								for (i = 0; m_base->inven[i].name != "나무"; i++);
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 2,1,5 };
									break;
								}
								else printf("자원이 모자랍니다.\n");
							}
						}
						else printf("그 공간에는 이미 시설이 존재합니다.\n");
					}
					else printf("유효한 값을 입력해주세요.\n");
					printf("그만두시겠습니까? (그만두려면 y 입력)>>");
					if (getchar() == ('y' || 'Y')) break;
					else printf("계속 진행합니다.");
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
							printf("나무를 %d개 소모합니다. 계속하시겠습니까?(y,n)>>", useitemcnt);
							char temp = getchar();
							bfclear();
							if (temp = ('y' || 'Y'))
							{
								for (i = 0; m_base->inven[i].name != "나무"; i++);
								if (m_base->inven[i].cur_cnt >= useitemcnt)
								{
									m_base->inven[i].cur_cnt -= useitemcnt;
									m_base->roomspace[roomnum - 1] = { 3,1,5 };
									break;
								}
								else printf("자원이 모자랍니다.\n");
							}
						}
						else printf("그 공간에는 이미 시설이 존재합니다.\n");
					}
					else printf("유효한 값을 입력해주세요.\n");
					printf("그만두시겠습니까? (그만두려면 y 입력)>>");
					if (getchar() == ('y' || 'Y')) break;
					else printf("계속 진행합니다.");
				}
				break;
			default:
				continue;
			}
		}
	}
}

int finditem(shelter* base)
{
	int srchbody;
	printf("1.나무 찾기,2.돌 찾기");
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
				printf("파견할 인원 수는?");
				scanf("%d", &srchbody);
				if (srchbody < base->curlife&&srchbody>0) break;
				else printf("파견인원은 최소 1인 이상은 되어야 하며, 기지에 한명 이상은 남아야 합니다.\n");
			}
			int rslt = rand() % (int)(srchbody * 1.5);
			for (i = 0; strcmp(base->inven[i].name, "나무") != 0; i++) if (i > 19) break;
			if (i < 20)
			{
				printf("나무를 %d개 찾았다!",rslt);
				for (int j = 0; rslt >= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
				printf("\t현재 갯수 %d개", base->inven[i].cur_cnt);
				if (rslt != 0) printf("공간이 모자라 %d개의 자원이 버려졌습니다.",rslt);
				printf("\n");
				return 1;
			}
			else { printf("에러:아이템의 저장위치를 찾을 수 없었습니다.\n"); return 0; }
		}
		else { printf("파견보낼 사람이 없습니다.\n"); return 0; }
		break;
	case '2':
		if (base->curlife > 0)
		{
			int i;
			while (1)
			{
				printf("파견할 인원 수는?");
				scanf("%d", &srchbody);
				if (srchbody < base->curlife&&srchbody>0) break;
				else printf("파견인원은 최소 1인 이상은 되어야 하며, 기지에 한명 이상은 남아야 합니다.\n");
			}
			int rslt = rand() % (int)(srchbody * 1.5);
			for (i = 0; strcmp(base->inven[i].name, "돌") != 0; i++) if (i > 19) break;
			if (i < 20)
			{
				printf("돌을 %d개 찾았다!", rslt);
				for (int j = 0; rslt >= 0; j++)
				{
					if (base->inven[i].cur_cnt >= base->inven[i].stackmax) break;
					base->inven[i].cur_cnt++; rslt--;
				}
				printf("\t현재 갯수 %d개", base->inven[i].cur_cnt);
				if (rslt != 0) printf("공간이 모자라 %d개의 자원이 버려졌습니다.", rslt);
				printf("\n");
				return 1;
			}
			else { printf("에러:아이템의 저장위치를 찾을 수 없었습니다.\n"); return 0; }
		}
		else { printf("파견보낼 사람이 없습니다.\n"); return 0; }
		break;
	default:
		printf("입력에서 오류가 있었습니다.\n");
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
			printf("파견할 인원 수는?");
			scanf("%d", &srchbody);
			if ((srchbody < base->curlife)&&(srchbody>0)) break;
			else printf("파견인원은 최소 1인 이상은 되어야 하며, 기지에 한명 이상은 남아야 합니다.\n");
		}
		int restemp;
		while (1)
		{
			printf("자원을 장비하여 보내면 사람을 더 구할 수 있을지도 모릅니다.\n1. 나무\n2.돌\n0. 장비하지 않는다.");
			char temp = getchar();
			switch (temp)
			{
			case '1':
				for (i = 0; base->inven[i].name != "나무"; i++) if (i>19) break;
				printf("%s:몇 개 사용하시겠습니까?");
				scanf("%d",&restemp);
				if (restemp < base->inven[i].cur_cnt&&restemp>0)
				{
					base->inven[i].cur_cnt -= restemp;
					rqpoint += restemp * 1;
					printf("%s %d 개 사용하였다.", base->inven[i].name, restemp);
				}
				else printf("갯수가 너무 크거나 작습니다.");
				break;
			case '2':
				for (i = 0; base->inven[i].name != "돌"; i++) if (i>19) break;
				printf("%s:몇 개 사용하시겠습니까?");
				scanf("%d", &restemp);
				if (restemp < base->inven[i].cur_cnt&&restemp>0)
				{
					base->inven[i].cur_cnt -= restemp;
					rqpoint += (int)(restemp * 1.5);
					printf("%s %d 개 사용하였다.\n", base->inven[i].name, restemp);
				}
				else printf("갯수가 너무 크거나 작습니다.\n");
				break;
			default:
				printf("잘못 입력하셨습니다.\n");
				break;
			}
			printf("자원추가를 더 할까요? (하지 않으려면 N 입력)");
			char lastpic = getchar();
			if (lastpic == ('N'||'n')) break;
		}
		int rslt = rand() % (srchbody / 5) + (rqpoint == 0 ? 0 : rand() % (rqpoint / 5));
		if (rslt + base->curlife < base->maxlife)
		{
			base->curlife += rslt;
			printf("%d명의 사람을 구하는데 성공했다\n", rslt);
		}
		else
		{
			int overbody = ((base->curlife + rslt) - base->maxlife);
			base->curlife += rslt - overbody;
			printf("%d명의 사람을 구출했지만, 정착지의 공간이 모자라 %d명의 사람들만 정착지에 들어왔다.\n",rslt,rslt-overbody);
		}
	}
	else printf("파견보낼 사람이 없습니다.\n");
}

void daytime(leader* user)
{
	int actcnt = DAYTIME_ACTCOUNT;
	printf("\t%s의 경로당\n", user->username);
	printf("------------------------------------------------\n\n");
	printf("                생존자 수 : %d\n\n", user->base->curlife);
	printf("------------------------------------------------\n\n");

	printf("지금은 낮 시간이다. 아무래도 좀비들의 활동이 줄어들 것 같다.\n");
	while (actcnt > 1)
	{
		printf("무엇을 할까?\n>> 경로당의 시설을 건설하자 (R)\n>> 자원을 찾으러 떠나자 (F)\n>> 조난당한 사람을 구하자  (S)\n\n알파벳 입력>>");
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
			printf("잘못 입력하셨습니다. 다시 입력하세요\n");
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
	strcpy(realuser.base->inven[3].name, "나무");
	strcpy(realuser.base->inven[4].name, "돌");


	printf("당신의 이름은 무엇입니까? (영어 20글자 한글 10글자 이내로)");
	scanf("%s", realuser.username);


	for (int i = 0; i < 20; i++)
		realuser.base->roomspace[i].roomtype = 0;
	while (1)
	{
		daytime(&realuser);
		break;
	}
}