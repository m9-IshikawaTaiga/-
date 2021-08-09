#include <iostream>
#include <vector>
#include <random>

#define CARD 52

using namespace std;

class Card
{

private:
    int hand;
    bool bursted = false;

public:
    bool stayed = false;

    int handcard()
    {
        return hand;
    };

    int burst()
    {
        return bursted;
    };

    int valueof(int card)
    {
        int cardnum;
        int cardtype;
        string type;

        cardnum = card % 13 + 1;
        cardtype = card / 13;
        if (cardtype == 0)
            type = "スペード";
        else if (cardtype == 1)
            type = "ハート";
        else if (cardtype == 2)
            type = "ダイヤ";
        else if (cardtype >= 3)
            type = "クローバー";
        cout << "カードは" << type << "の" << cardnum << endl;

        if (cardnum >= 11)
            cardnum = 10;

        return cardnum;
    };

    void hit(vector<int> &deck)
    {
        int newcard;
        newcard = deck.back();
        deck.pop_back();
        if (newcard == 1)
        {
            while (hand < 10)
            {
                newcard = 11;
            }
        }
        hand = hand + valueof(newcard);
        if (hand > 21)
            bursted = true;
    };
};

int main()
{
    vector<int> cardlist(CARD);

    for (int i = 0; i < CARD; i++)
    {
        cardlist[i] = i;
    }
    random_device seed_gen;
    mt19937 engine(seed_gen());
    shuffle(cardlist.begin(), cardlist.end(), engine);

    Card you;
    Card cpu;

    cout << "【CPUのカード】" << endl;
    cpu.hit(cardlist);

    cout << "あなたの番です。" << endl;
    cout << "【あなたのカード】" << endl;
    you.hit(cardlist);
    you.hit(cardlist);
    cout << "あなたのカードは " << you.handcard() << endl;

    char stay = '1';

    while (!you.burst())
    {
        cout << "ステイなら0、続けるなら1を入力してください。" << endl;
        cin >> stay;
        if (stay == '0')
            break;
        you.hit(cardlist);

        cout << "あなたの手札は " << you.handcard() << endl;
    };

    if (stay != '0')
    {
        cout << "あなたはバーストしました。" << endl;
        goto YOU_LOSE;
    }
    cout << "CPUの番です。" << endl;

    while (cpu.handcard() < 17)
    {
        cpu.hit(cardlist);
        cout << "CPUの手札は" << cpu.handcard() << endl;
        ;
    };

    if (cpu.burst())
    {
        cout << "CPUがバーストしました。" << endl;
        goto YOU_WIN;
    }

    cout << "【結果】" << endl;
    cout << "あなたの手札は" << cpu.handcard() << endl;
    cout << "CPUの手札は" << cpu.handcard() << endl;

    if (you.handcard() > cpu.handcard())
    {
        goto YOU_WIN;
    }
    else if (you.handcard() == cpu.handcard())
    {
        goto DEAL_GAME;
    }
    else if (you.handcard() < cpu.handcard())
    {
        goto YOU_LOSE;
    }

YOU_WIN:
    cout << "あなたの勝ちです。" << endl;
    return 0;

DEAL_GAME:
    cout << "引き分けです" << endl;
    return 0;

YOU_LOSE:
    cout << "あなたの負けです。" << endl;
    return 0;
}

