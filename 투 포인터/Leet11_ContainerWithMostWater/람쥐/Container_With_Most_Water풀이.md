https://leetcode.com/problems/container-with-most-water/?envType=problem-list-v2&envId=array

### 설명 
리트코드의 기본적인 11번 문제 최대 용량의 물을 채우는 방식의 문제입니다. 이 문제는 완전탐색이 아닌 투포인터를 이용해서 풀 것을 강조하고 있으며, 투 포인터를 이용해서 두 벽을 검색하면서 max 값을 탐색하는 방식입니다. 
난이도 자체는 어렵지 않으나, 투포인터등의 탐색 방식이 얼마나 효율적으로 탐색가능한지 수치상으로 확인가능한 연습문제입니다. 

```cpp
class Solution {

public:

    int maxArea(vector<int>& height) {

        int i = 0; int j =height.size()-1;

        int answer = 0 ;

        int h = 0;

  

        while(i < j )

        {

            int h = min (height[i], height[j]);

            answer = max (answer, h*(j-i));

            if (height [i] < height[j])

            {

                i++;

            }

            else

             {

                j--;

            }

        }

        return answer;

    }

};
```

![[Pasted image 20250918205024.png]]

시간복잡도와 메모 공간복잡도에 매우 아쉽다고 생각 되어 한번 최적화를 해봅시다. 

가장 좋은 최적화 방식은, 로컬변수에 캐싱한뒤, 탐색하는 것이 첫번째, 그리고 min max를 빼버리고, 단순 조건문을 사용하는 것입니다. min,max는 탬플릿 함수이기때문에 인라인 되더라도 분기비용을 지불해야하며, 시간 복잡도에서 손해를 볼 수 있습니다.

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0; 
        int j =height.size()-1; 
        int answer = 0 ;
        int h = 0; 

        while(i < j )
        { 
            int left = height[i];
            int right = height[j]; // 왼쪽 오른쪽은 모두 캐싱 

            if (left < right )
            { 
                int area = left * (j - i); 
                if (area > answer) answer = area; // min,max 인라인 연산보다는 직접 비교 연산. 
                ++ i; 
            }
           else 
            {
                int area = right *(j-i); 
                if (area >answer) answer = area; 
                --j;
            }
           
        }
        return answer; 
    }
};
```

![[Pasted image 20250918210431.png]]
주요 변수 캐싱, 그리고 min/max 탬플릿 함수가 아닌 직접 비교를 통해 확실히 시간복잡도를 끌어냈습니다. 메모리를 많이 사용하게 되지만, 이 이상으로 메모리를 절약하는게 큰 의미가 없어보여, 시간 복잡도를 낮춘 것만으로도 충분히 만족합시다.

### 시간 초과 난 풀이


```cpp


class Solution {
public:
    int maxArea(vector<int>& height) {
        int answer = 0 ;
        int h = 0; 

        for(int i = 0 ; i < height.size() -1 ; i++)
        {
            for (int j = height.size()-1 ; j >= 0 ; j --)
            { 
               
                h = min(height[i], height[j]);
                
               answer = max(answer, (j-i)*h);

            }
            
        }
        return answer; 
    }
};

```

위 풀이는 O(n^2) 이기 때문에 상대적으로 시간복잡도 면에서 손해를 많이 봅니다. 투포인터가 얼마나 시간복잡도를 낮춰 줄수있는지를 보여줄수있는 문제입니다. 