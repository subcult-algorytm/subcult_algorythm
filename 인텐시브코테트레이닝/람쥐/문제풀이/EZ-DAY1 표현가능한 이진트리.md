
**2023 카카오 블라인드 채용 -  4번 문제** 

카카오 공식풀이 - https://tech.kakao.com/posts/567


- 더미 노드를 만들어서 포화 이진트리를 만들고
- 노드를 왼족에 있는 순서대로 살펴보며 더미는 0, 실제 노드는 1로 생성해서 문자열에 추가합니다. 
- 그렇게 해서 만든 이진수를 십진수로 만듭니다. 

### 난이도 

Lvl 3의 문제로 책정되었으며, 카카오 코테에서도 중간 급 난이도로 책정되었습니다. 보통 카카오급 공채 중간급이면 클라 코테에서는 상위권으로 책정되겠지만, 뜯어보면 주제 자체가 그리 어렵지 않은 저난이도 주제라 클라 코테에서도 초반부에 충분히 만날 수있는 난이도라 생각됩니다.

### 키워드

주요 키워드 
분할정복, 문자열

### Input

이진트리로 만들고 싶은, 수를 1차원 정수배열 numbers 에 담습니다. 주어진 수대로 하나의 이진트리로 해당수를 표현할수있다면 1, 표현할수없다면 0을 담아 result 배열에 담습니다. 

### 풀이 전략 

프로그래머스의 전형적인 **페이크성 문제**로, 이진트리같아 보이지만 정말로 이진트리를 구현해서 하면 돌아버리는 난이도가 됩니다. 설계를 충분히 하지않고, 코드부터 치면 무조건 말리는 문제라 생각됩니다. 

중반부 문제가 그렇게 어렵게 풀린다면 무조건 풀이가 꼬인것이며, 분명 쉬운길이 있다는걸 알아야 합니다. 특히 이런식의 서술형 문제들은 풀기전에, 꼭꼭 필요한 정보가 뭔지를 파악하고 푸는 것이 중요하다 볼 수 있겠습니다.  정말 필요한 Binary (이진수)의 String을 이용하는 문제라는걸 생각하면 이진트리와는 관련이 적은 문제임을 알수 있습니다.

이진트리를 DFS로 쓸수 있지만, 분할정복을 통해 푸는게 일반적이어 보입니다. 분할정복 알고리즘을 이용 문자열을 조작하는 문제라, 문자열 매서드들을 잘쓰는게 중요합니다. 

이진수는 앞에 0을 붙여도 같은 값이라는걸 생각해보면 조금 답이 나옵니다. 그리고 이진수 문자열의 **중간값은 무조건 1이어야지만**, 트리가 성립되나, 서브 트리의 경우 중간값이 1이 아니어도 트리가 성립됩니다.

그렇기 때문에, 42, 95 같이 숫자만으로 이진트리가 안나오는 것은 앞에 0을 붙여 더미 노드를 만들고, 중간값을 1로 만들어서, 포화 이진트리를 만들어 줄수 있습니다. 앞에 붙이는 것이니. `Deque` 를 사용해볼 수도 있겠습니다. 

7-> 111 -> 왼쪽 오른쪽을 가진 트리가 만들어집니다.
42 -> 101010 하지만 0 추가하면 7과 비슷한 모양 

5 -> 00101

95 -> 101111, 앞에 0을 추가하면 왼쪽이 비대칭적인 트리가 만들어집니다. 


포화 이진트리의 총 크기는 `(2^n)-1` 입니다. 만약 String의 크기가 이에 맞지 않다면 저 크기에 맞춰서 더미 노드를 만들어 주어야 합니다. 

위와 같은 로직을 이용해서 중앙 노드와 서브노드를 모두 분할정복하면 됩니다.


첫번째로 10진수를 2진수로 만듭니다. 

```cpp
#include <iostream>
#include <string>
using namespace std;

int get_binary(long long n)
{
    string binary = "";

    while (n != 0)
    {
        binary += to_string(n % 2);
        n /= 2;
    }

    return binary;
}
```

https://maloveforme.tistory.com/179

귀찮으니 갖다 씁니다. 함수 하나하나 생각하면서 기억을 더듬어 하기에는 시간이 없습니다.        

포화 이진트리, 크기를 2^n - 1로 만들어주는 로직을 만듭니다

```cpp
string makeFullTree(string str)
{ 
    string fullStr = str; 
    int indx = 2; 
    while (true)
    { 
        if(str.length () <= indx - 1) break; 
        indx *=2; 
    }
    for (int i = 0; i < indx - 1 - str.length(); i++)
    {
        fullStr = "0" + fullStr;
    }
    return fullStr;   
}

```

앞서 말했던 서브 트리의 모든부분이 0인 케이스를 만듭니다.

```cpp
bool isAllzero(string str){
    
    for (char c : str)
    {
        if (c != '0')
            return false; 
    }
    return true; 
}


```

이제 트리가 만들어지는지 판별하는 로직을 만들고, 적용합니다 

```cpp

int CanMakeTree (string inBinary)
{ 
    if (inBinary.length() == 1 || isAllzero(inBinary))
    {
        return 1;
    }
    int middle = inBinary.size()/2;
    string left = inBinary.substr(0, middle); 
    string right = inBinary.substr(middle+1); 
    
    if (inBinary[middle] == '1' && CanMakeTree(left) && CanMakeTree(right))
         { 
            return 1; 
         }
            return 0; 

   
}
```

### 예제는 맞으나 테스트 케이스가 실패 
```cpp 

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string makeBinary (int a){  

   string binary = "";

    while (a != 0)
    {
        binary += to_string(a % 2);
        a /= 2;
    }

    reverse(binary.begin(), binary.end());

    return binary;
}

string makeFullTree(string str)
{ 
    string fullStr = str; 
    int indx = 2; 
    while (true)
    { 
        if(str.length () <= indx - 1) break; 
        indx *=2; 
    }
    for (int i = 0; i < indx - 1 - str.length(); i++)
    {
        fullStr = "0" + fullStr;
    }
    return fullStr;   
}

bool isAllzero(string str){
    
    for (char c : str)
    {
        if (c != 0)
            return false; 
    }
    return true; 
}

int CanMakeTree (string inBinary)
{ 
    if (inBinary.length() == 1 || isAllzero(inBinary))
    {
        return 1;
    }
    int middle = inBinary.size()/2;
    string left = inBinary.substr(0, middle); 
    string right = inBinary.substr(middle+1); 
    
    if (inBinary[middle] == '1' && CanMakeTree(left) && CanMakeTree(right))
         { 
            return 1; 
         }
            return 0; 

   
}
vector<int> solution(vector<long long> numbers) {
    
    vector<int> answer;
    vector<string> binaryContainers; 
    
    
    // 1. make the numbers as the 2digts 
    
    for (long long i = 0 ; i < numbers.size(); i ++)
    { 
        string euhe = makeBinary(numbers[i]);
        string bigEhee = makeFullTree(euhe);
        answer.push_back(CanMakeTree(bigEhee));
    }

    
    return answer; 
}
```

간단한 실수 때문이었는데...

```cpp 

string makeBinary (int a){  

   string binary = "";

    while (a != 0)
    {
        binary += to_string(a % 2);
        a /= 2;
    }

    reverse(binary.begin(), binary.end());

    return binary;
}

/// 
```

인자를 long long 이 아닌 int로 받은점과, 

```cpp

bool isAllzero(string str){
    
    for (char c : str)
    {
        if (c != 0) // 이 부분이 문자이어야 함. 
            return false; 
    }
    return true; 
}
```


그리고 저기에 있는 0을 문자로 바꾸는순간, 모든 테스트케이스에서 통과 되었습니다. 


```cpp 

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string makeBinary (long long a){  

   string binary = "";

    while (a)
    {
        binary = to_string(a % 2) + binary;
        a /= 2;
    }

    return binary;
}

string makeFullTree(string str)
{ 
    string fullStr = str; 
    int indx = 2; 
    while (true)
    { 
        if(str.length () <= indx - 1) break; 
        indx *=2; 
    }
    for (int i = 0; i < indx - 1 - str.length(); i++)
    {
        fullStr = "0" + fullStr;
    }
    return fullStr;   
}

bool isAllzero(string str){
    
    for (char c : str)
    {
        if (c != '0')
            return false; 
    }
    return true; 
}

int CanMakeTree (string inBinary)
{ 
    if (inBinary.length() == 1 || isAllzero(inBinary))
    {
        return 1;
    }
    int middle = inBinary.length()/2;
    string left = inBinary.substr(0, middle); 
    string right = inBinary.substr(middle+1); 
    
    if (inBinary[middle] == '1' && CanMakeTree(left) && CanMakeTree(right))
    { 
        return 1; 
    }
    else 
    { 
        return 0; 
    }
    

   
}
vector<int> solution(vector<long long> numbers) {
    
    vector<int> answer;
    vector<string> binaryContainers; 
    
    
    // 1. make the numbers as the 2digts 
    
    for (long long & num : numbers)
    { 
        string euhe = makeBinary(num);
        string bigEhee = makeFullTree(euhe);
        answer.push_back(CanMakeTree(bigEhee));
    }

    
    return answer; 
}
```

### 다른풀이 

비트연산자로도 풀 수 있습니다. 

![[Pasted image 20250905040802.png]]


### 유의할점 

크게 유의 할점은 없으나, 프로그레머스와 같은 장문형 문제들의 특징인 "**읽어봤더니 다른걸 물어보고 있더라**" 유형에 가까워 이 점을 주의 해야합니다. 