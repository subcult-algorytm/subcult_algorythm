
코테에서 자주 쓰이는 문법 컨테이너 모음. 

---
## 자주쓰는 문법 
### Call by Reference vs Call by Value

Call by Value - 복사해서 값을 전달, 성능에 영향 큼, 원래의 값은 변화 없음 
Call by reference - 주소값 전달, 성능에 영향 적음, 원래의 값을 변화함. 
	- 참조값 (&) 전달방식 - 참조변수와 참조대상의 주소값 일치 
	- 주소값 ( * ) 전달 방식 - 참조변수와 실제변수의 주소값이 달라, 포인터 변수 사용해야함. 

```cpp  

void modify(int& value)
{ 
	value = 10; // 같은 주소 
}

int main () 
{ 
int value = 5; // 5 , 같은 주소 
modify (value);

cout << value << endl; // 10. 

}
```

큰 컨테이너는 참조값으로 전달하세요. 
(포인터 실수 방지)


#### 반복문 쓰기 

```cpp

// 전구간 순회시 
for ( auto 변수명 : 순회할 컨테이너)

// 후순위 순회나 특정 구간 순회이면 
for (타입 변수명 ; 변수명 < 컨테이너 크기 ; 변수 ++ or 변수 --)

```



## 컨테이너 

저장된 데이터에 배열처럼 임의 접근 = 벡터 
키-값으로 저장해야하는 해시 테이블 같은것 = 맵 

#### Vector 

 ```cpp
 
 // 빈 2차원 벡터
 vector<vector<int>> v1;
 
 // 특정 크기로 초기화 하기 
 int rows = 3;
 int rows = 4; 
 
 vector<vector <int>> v2 (rows, vector<int>(cols));
 
 // 특정 값으로 초기화하기 
 int val 9; 
 vector<vector<int>> v3 (row, vector<int>(cols, val));
 
 
 // 초기화 리스트 이용한 2차원 벡터 초기화 
vector<vector<int>> v4 = { 
	{1, 2, 3}, 
	{1, 2, 3}, 
	{1, 2, 3}, 
}
 ```



```cpp
//특정 값 바꾸기 
v2[3][2] = 10; 


// 뒤에 삽입하기 
v.push_back(5);

// 맨뒤 빼기 
v.pop_back();

// 맨앞에 넣기
v.insert(v.begin, 1); 

// 맨앞에 빼기
v.erase(v.begin()); 

```

맨 앞의 원소를 삭제할 일이 많으면 Deque 사용하기. 


### 셋 

중복 허용 X 저장된 데이터 자동으로 정렬 , **균형 이진트리 사용.** 

```cpp 
// 원소탐색 
set<int> numbers; 

//원소탐색은 .find() 메서드로. 
numbers.find(target); 
```


### 맵 

키와 값을 쌍으로 갖는 컨테이너 - 헤시 테이블이나, 값을 쌍으로 가져야하는 경우 사용. 

```cpp 

map <string, double> EmployeeSalaeries; 

// 이름과 Double 값을 쌍으로 가짐, 

map <string, double> EmployeeSalaeries = {
	{"Alex", 65000} // 초기화시 모든 메서드 입력해야함
}
```

특정키에 접근 

```cpp
EmployeeSalaeries ["Alice"]; // Alice에 접근, 없으면, 생성 

EmployeeSalaeries.find("Alex"); // find() 메서드, 있으면 찾고, 없으면 예외처리. 
```

변경

```cpp 

EmployeeSalaries ["Alex"] = 75000; // 알렉스를 찾음 -> 75000으로 변경 
```

삽입 삭제 

앞서말했듯이, 괄호 연산자로 새로운 키 생성 가능. 
`Insert()` 메서드도 사용가능 .

```cpp 
EmployeeSalaeries,insert(["Alice", 68000]); // 된다
EmployeeSalaeries.insert(make_pair("Fukka", 75000)); // 된다. 

EmployeeSalaeries.erase("Alex")// 알렉스 삭제.  
```



##  컨테이너와 함께 쓰는 STL 문법 

### Count()

```cpp 
int ret = count (v.begin(), v.end(), 5);

// v 라는 컨테이너에, 5를 찾고, 5가 얼마나 있는지 반환한다. 
```


### Sort() 

```cpp 

sort (v.begin(), v.end()); // 오름차순 정렬 

sort(v.rbegin(), vrend()); // 내림차순 정렬
```


### `next _permutation()` 

가능한 모든 순열 생성하기 
``` cpp 
next_permutation(v.begin(), v.end()); 
```


### `Unique()`

중복되는 원소는 뒤로 밀어버리고, 제거하기. 

```cpp
unique(v.begin(), v.end());
```


### `min_element()` `max_element()`

컨테이너 안의 최소 최대값 구하기