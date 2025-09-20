https://www.hackerrank.com/challenges/counter-game/problem?isFullScreen=true

HackersRank의 카운터 게임 문제로, 비트마스크 연산을 사용해야만 풀수있는 문제입니다.

비트마스크 문제 특성상 알면 풀고 모르면 Timeout 먹고 맞아야지 성격이 강합니다. 


처음 주어진 숫자를 2의 배수로 줄이거나, XOR 오퍼레이션을 해서 현재의 숫자보다 줄이면 됩니다. 

> [!NOTE]
> 주어진 숫자가 2의 배수라고 하면 2로 나누면 됩니다. 
> 주어진 숫자가 2의 배수가 아니면 XOR 오퍼레이션이 필요합니다.  XOR 오퍼레이션을 한 수를 빼서 반환합니다.
> 1이면  Richard가 승리하게 됩니다. 


```cpp

long PowerOfTwo(long n)

{
    if (n == 0)

    {
        return 0;
    }

    n--;

    n |= (n >> 1);

    n |= (n >> 2);

    n |= (n >> 4);

    n |= (n >> 8);

    n |= (n >> 16);

    n |= (n >> 32);

    return n - (n >> 1);

	// 비트마스크 연산이 들어간 곳.

}

  

string Winner (bool win)

{

    if(win)

    {

        return string("Louise");

    }

    return string("Richard");

}

  

string counterGame(long n) {

    if ( n == 1)

    {

        return "Richard";

    }

    long Counter = n;

    bool win = false;

    while(Counter > 1)

     {

        if (Counter%2 == 0)

        {

            Counter = Counter/2;

        }

        else

        {

           Counter = Counter - PowerOfTwo(Counter);

        }

        win =! win;
        // 승리인지 아닌지 역시도 비트마스크로 연산합니다. 

     }

   return Winner(win);

}

```

### 유의할점 

비트마스크 조작으로 배열문제를 풀수도 있음을 기억합시다. 