//      Copyright [2019] <ZhaoYunhao,ZhuMingxi,WangZeyu,YinCheng>
//      21Point.cpp
//      2019.12.10


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <algorithm>
#include <time.h>
constexpr auto __user = 1;
constexpr auto __ai = 2;
void reset();
struct Poker    //     扑克牌结构体 顺序生成52张
{
    short color;   //      扑克花色 1-黑桃 2-红桃 3-草花 4-方片
    short numb;   //      扑克牌值 j-11 q-12 k-13
    bool used;   //    记录该牌是否使用 0-可用 1-已用
    //     No Jocker
}card[53];
int User_Card[12];
int Ai_Card[12];
int User_Card_Number = 0;
int Ai_Card_Number = 0;
int Game_Mod = 0;   //    0-随机 1-调教
int AI;
void BuildCard()    //    为方便记录本题所有值从1开始计数
{
    int now = 1;    //    从1开始
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 13; j++)
        {
            card[now].color = i;
            card[now].numb = j;
            card[now].used = 0;
            now++;
        }
    }
    return;
}
void Send_Poker(int who)    //    模拟发牌 初始发2张 后来一次一张
{
    srand((unsigned)time(NULL));
    int need;
    if (who == 1)
    {
        if (User_Card_Number == 0)need = 2;
        else need = 1;
        for (int i = 0; i < need; i++)
        {
            int pos;
            do pos = rand() % 52 + 1;
            while (card[pos].used);  // NOLINT
            User_Card[User_Card_Number + 1] = pos;
            card[pos].used = 1;
            User_Card_Number++;
        }
    }
    if (who == 2)
    {
        if (Ai_Card_Number == 0)
        {
            need = 2;
        }
        else need = 1;
        for (int i = 0; i < need; i++)
        {
            int pos;
            do pos = rand() % 52 + 1;
            while (card[pos].used);// NOLINT
            Ai_Card[Ai_Card_Number + 1] = pos;
            card[pos].used = 1;
            Ai_Card_Number++;
        }
    }
    return;
}
int Count_Card()    //    记录剩下的牌数
{
    int left = 0;
    for (int i = 1; i <= 53; i++) if (card[i].used == 0) left++;
    return left;
}
int Count_Card_Number()    //    记录剩余总点数
{
    int all = 0;
    for (int i = 1; i <= 53; i++)
        if (card[i].used == 0)
            if (card[Ai_Card[Ai_Card_Number]].numb >= 10)all += 10;
            else all += card[Ai_Card[Ai_Card_Number]].numb;
    return all;
}
int Judgeai()    //    Ai判断->比较距离21点的点数和剩余的平均点数,相差在合理范围内即判断抓牌
{
    int aitt = 0;
    for (int i = 1; i <= Ai_Card_Number; i++)
        if (card[Ai_Card[i]].numb >= 10)aitt += 10;
        else aitt += card[Ai_Card[i]].numb;
    int dt = 21 - aitt;
    float exp = (float)Count_Card_Number() / (float)Count_Card();
    float ans = abs(dt - exp);
    if (ans < AI) return 1;
    else return 0;
}
void mod_set()    //    欢迎界面
{
    printf("---------------------------------------------------------------------------------\n");
    printf("---                   欢迎来到澳门顶级赌场21点分会场！                        ---\n");
    printf("---                       性感周柏杨在线发牌                                  ---\n");
    printf("---                                                                           ---\n");
    printf("---  请选择游戏模式：                                                         ---\n");
    printf("---                                                                           ---\n");
    printf("---          1.随机模式                                                       ---\n");
    printf("---            在随机模式中，Ai的参数是随机的~~~~~~                           ---\n");
    printf("---                                                                           ---\n");
    printf("---          2.自定模式                                                       ---\n");
    printf("---            在自定模式中，你可以自己调♂教Ai的参数使自己更加快乐 ~         ---\n");
    printf("---                                                                           ---\n");
    printf("---                                                                           ---\n");
    printf("---                                                                           ---\n");
    printf("---  按下你手中的1或2,即可进入新葡京的大门~~~                                 ---\n");
    printf("---                                                                           ---\n");
    printf("---                                                                           ---\n");
    printf("---------------------------------------------------------------------------------\n");
    //    scanf("%d", &Game_Mod);
    char in[100] = "null";    //    防止乱输
    gets_s(in);
    while (strlen(in) != 1 || (in[0] != '1' && in[0] != '2'))
    {
        printf("周柏杨♂还小，听不懂你在说什么哦~~\n重新输入吧：");
        gets_s(in);
    }
    if (in[0] == '1')
    {
        Game_Mod = 1;
    }
    else Game_Mod = 2;
    system("cls");
    return;
}
void Print_Card(int Card_number)    //    输出牌
{
    switch (card[Card_number].color)
    {
    case 1: printf("黑桃"); break;
    case 2: printf("红桃"); break;
    case 3: printf("草花"); break;
    case 4: printf("方片"); break;
    default: break;
    }
    if (card[Card_number].numb <= 10)printf(" %d    ", card[Card_number].numb);
    else if (card[Card_number].numb == 11) printf(" J    ");
    else if (card[Card_number].numb == 12) printf(" Q    ");
    else if (card[Card_number].numb == 13) printf(" K    ");
    return;
}
int Judge21()    //    判断是否达到结束条件
{
    int User_Point = 0;
    int Ai_Point = 0;
    for (int i = 1; i <= User_Card_Number; i++)
    {
        User_Point += min(10, card[User_Card[i]].numb);
        //    printf("user:%d\n", User_Point);
    }
    for (int i = 1; i <= Ai_Card_Number; i++)
    {
        Ai_Point += min(10, card[Ai_Card[i]].numb);
    }
    return (User_Point >= 21 || Ai_Point >= 21);
}
void Gameover()    //    结束界面
{
    system("cls");
    int User_Point = 0;
    int Ai_Point = 0;
    for (int i = 1; i <= User_Card_Number; i++)
    {
        User_Point += min(10, card[User_Card[i]].numb);
    }
    for (int i = 1; i <= Ai_Card_Number; i++)
    {
        Ai_Point += min(10, card[Ai_Card[i]].numb);
    }
    printf("游戏结束啦~~\n");
    printf("你的牌：");
    for (int i = 1; i <= User_Card_Number; i++) Print_Card(User_Card[i]);
    printf("\n点数和为：%d\n\n", User_Point);
    printf("Ai的牌：");
    for (int i = 1; i <= Ai_Card_Number; i++) Print_Card(Ai_Card[i]);
    printf("\n点数和为：%d\n\n\n\n\n", Ai_Point);
    int Winner = 1;
    if (Ai_Point > 21 && User_Point > 21) Winner = 0;
    else if (Ai_Point > 21) Winner = -1;
    else if (User_Point > 21) Winner = 1;
    else if (Ai_Point == User_Point) Winner = 0;
    else if (Ai_Point > User_Point) Winner = 1;
    else Winner = -1;
    printf("根据周柏杨的判♂断：此次游戏获胜者为");
    if (Winner == 1) printf(" AI \n看来你还要加把劲啦~~~");
    else if (Winner == -1) printf(" 你 \n看来你的运气还不错，下次更换参数再来试试运气吧！\n\n");
    else printf(" 周柏杨 因为你们都没有获胜！");
    printf("按下任意键回到初始界面！");
    getchar();
    getchar();
    system("cls");
    mod_set();
    reset();
}
void Game(int num)    //    游戏主体,递归进行
{
    system("cls");
    printf("现在是第%d轮游戏啦~~\n", num);
    printf("你的参数：%d~~\n", AI);
    printf("\n");
    printf("你的牌：");
    for (int i = 1; i <= User_Card_Number; i++)
    {
        Print_Card(User_Card[i]);
    }
    printf("\n");
    printf("Ai的牌：");
    for (int i = 1; i <= Ai_Card_Number; i++)
    {
        Print_Card(Ai_Card[i]);
    }
    printf("\n");
    if (Judge21())
    {
        Gameover();
    }
    printf("是否继续抓牌？");
    printf("输入1继续抓牌，输入0放弃抓牌");
    char in[1001] = "Null";
    gets_s(in);
    while ((strlen(in) != 1 || (in[0] != '1' && in[0] != '0')))
    {
        printf("请好好输入，不可以搞事哦~~\n重新输入吧：");
        gets_s(in);
    }
    if (in[0] == '1')
    {
        Send_Poker(__user);
        if (Judgeai()) Send_Poker(__ai);
        if (Judge21()) Gameover();
    }
    else if (in[0] == '0')
    {
        if (Judgeai()) Send_Poker(__ai);
        else Gameover();
        if (Judge21()) Gameover();
    }
    else Gameover();
    printf("请按任意键进入到下一回合！");
    getchar();
    Game(num + 1);
}
void reset()
{
    BuildCard();
    User_Card_Number = 0;
    Ai_Card_Number = 0;
    Send_Poker(__user);
    if (Game_Mod == 2)
    {
        printf("你想怎么调教Ai呢\n");
        printf("好了你说个整数吧:");
        char in[1001] = "Null";
        int flag = 1;
        while (flag)
        {
            gets_s(in);
            for (int i = 0; i < strlen(in); i++)
            {
                if (in[i] > '9' || in[i] < '0')
                {
                    printf("请好好输入，不可以搞事哦~~\n重新输入吧：");
                    flag = 1;
                    break;
                }
                flag = 0;
            }
        }
        sscanf(in, "%d", &AI);
        printf("Ai还是个小孩子呢~希望你的参数能帮助我长大！");
        AI = AI % 19 + 1;
        printf("\n请按任意键开始愉快的游♂戏！");
        getchar();
        getchar();
    }
    else
    {
        printf("随机随机啦\n");
        srand((unsigned)time(NULL));
        AI = rand() % 19 + 1;
        printf("众所周知，没有绝对的随机\n");
        printf("所以根据周柏杨的一系列运算，得到了Ai参数：%d", AI);
        printf("\n请按任意键开始愉快的游♂戏！");
        getchar();
        getchar();
    }
    Send_Poker(__ai);
    system("cls");
    Game(1);
    return;
}
int main()     //    主函数
{
    mod_set();
    reset();
    return 0;
}
