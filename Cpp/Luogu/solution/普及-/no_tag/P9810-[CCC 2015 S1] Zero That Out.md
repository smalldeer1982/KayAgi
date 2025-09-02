# [CCC 2015 S1] Zero That Out

## 题目描述

给定 $k$ 个整数 $a_{1 \dots k}$，维护一个序列，按顺序进行以下操作：

- 当 $a_{i} = 0$ 时，将序列中最后加入的数删除。
- 否则，将 $a_{i}$ 加入序列。

例如：当 $a = \{1,3,5,4,0,0,7,0,0,6\}$ 时，操作如下。

|$a_{i}$|序列|
|:--:|:--:|
|$1$|$\{1\}$|
|$3$|$\{1,3\}$|
|$5$|$\{1,3,5\}$|
|$4$|$\{1,3,5,4\}$|
|$0$|$\{1,3,5\}$|
|$0$|$\{1,3\}$|
|$7$|$\{1,3,7\}$|
|$0$|$\{1,3\}$|
|$0$|$\{1\}$|
|$6$|$\{1,6\}$|

你需要计算最终序列中所有数的和。

## 说明/提示

**【数据范围】：**

$1 \leq k \leq 10^{5}$，$0 \leq a_{i} \leq 100$。

保证在 $a_{i} = 0$ 时序列不为空。

## 样例 #1

### 输入

```
4
3
0
4
0```

### 输出

```
0```

## 样例 #2

### 输入

```
10
1
3
5
4
0
0
7
0
0
6```

### 输出

```
7```

# 题解

## 作者：Lovely_Elaina (赞：10)

显然可以简化题意为模拟一个栈。

$T$ 次操作，每次给一个数 $x$。当 $x=0$ 时弹出栈元素，否则栈压入新的元素 $x$，最后求栈内所有元素的和。

数据不大，用一个数组模拟即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;

int T,x;
int k,a[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
    cin >> T;
    while(T--){
        cin >> x;
        
        if(x) a[++k] = x;
        else k--;
    }
    
    int cnt = 0;
    for(int i = 1; i <= k; i++)
        cnt += a[i];
    cout << cnt << endl;
	return 0;
}
```

---

## 作者：Jasoncwx (赞：1)

## 题目思路
对于这道题，我们可以使用栈进行模拟。我们定义栈的名称为 $s$。

如果 $t=0$，因为栈的原理是后进先出，所以我们可以让 $s$ 中最开头的数出栈，即 `s.pop()`。

否则我们直接把 $t$ 入栈，即 `s.push(t)`。

最后我们只需要算出在 $s$ 里所有数的和即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,sum=0;
    cin>>n;
    stack<int>s;
    while(n--){
        int t;cin>>t;
        if(!t)s.pop();//出栈
        else s.push(t);//入栈
    }
    while(!s.empty()){//判断栈是否为空
        sum+=s.top();
        s.pop(); 
    }
    cout<<sum;
}
```


---

## 作者：SunnyLi (赞：0)

# 思路

这种题，直接 Python 模拟即可。声明一个列表 `a`，如果输入 `t` 等于 $0$，那么删除 `a` 的最后一个元素，即进行 `a.pop()` 操作，否则添加该元素，即 `a.append(t)`。

# AC 代码

```python
a = []
k = int(input())
for i in range(k):
    t = int(input())
    if(t==0):
        a.pop()
    else:
        a.append(t)
print(sum(a))
```

---

## 作者：BugGod (赞：0)

由 $a_i=0$ 的情况直接想到栈，我们可以开一个栈维护这个序列，再开一个 `sum` 动态维护序列和，具体看代码。

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,sum,a;
stack<int>s;
int main()
{
    cin>>k;
    while(k--)
    {
        cin>>a;
        if(a==0)//删除操作
        {
            if(s.size())
            {
                sum-=s.top();//删除了这个数，对于和来说，就要减去这个数
                s.pop();
            }
        }
        else
        {
            sum+=a;
            s.push(a);
        }
    }
    cout<<sum;
    return 0;
}
```

---

## 作者：jqQt0220 (赞：0)

~~好臭的题号~~

题意十分简洁明了，不在此赘述。本来想着能有啥高大上的做法呢，结果一看数据范围：$1\le k\le10^{5}$，直接模拟就行。

可以用栈模拟这个序列（数据范围很小，不想抢最优解的话就不用管常数多大，直接用 `std::stack` 就行了），为了减去求和的时间复杂度，可以直接边输入边加，如果 $a_i=0$ 就和减去栈顶元素，然后弹出，否则入栈并累加。最后输出就搞定了。

AC Code：（我的代码前面有些奇奇怪怪的初始化，这里连头文件一起省略了）
```cpp
int k,a,as=0;
stack<int> s;
int main()
{
    ___();//这是我写的初始化函数，就是 cin cout 去同步，可以直接忽略，好奇的可以看我煮液里缺省源的链接
    cin>>k;
    while(k--)//执行 k 次
    {
        cin>>a;
        if(a==0)
            as-=s.top(),s.pop();//和减去栈顶并弹栈
        else
            s.push(a),as+=a;//和加上 a 并入栈
    }
    cout<<as<<endl;//AT 养成的输出换行好习惯
    return 0;//完美结束 QwQ
}
```

---

## 作者：Vct14 (赞：0)

因为本题只在序列末端加入元素，而且只会删除序列中最后加入的数，那么很容易想到栈。

题目可以化为给定一个长度为 $n$ 的序列 $a$，对于 $a_i$，当 $a_i=0$ 时，将栈顶出栈，否则将 $a_i$ 压入栈中。最后统计和时，我们可以累加栈顶元素，然后将它出栈，直到栈空为止。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int k;
	cin>>k;
	stack<int> s;
	while(k--){
		int a;cin>>a;
		if(a) s.push(a);
		else s.pop();
	}
	int sum=0;
	while(!s.empty()){
		sum+=s.top();
		s.pop();
	}
	cout<<sum;
	return 0;
}
```

---

