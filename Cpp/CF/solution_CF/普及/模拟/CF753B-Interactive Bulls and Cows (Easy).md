# Interactive Bulls and Cows (Easy)

## 题目描述

交互题

一个脍炙人口的猜数游戏。

在一张纸上，一位玩家写下一个四位数（保证各位数码不重复，不含前导零）。第二位玩家尝试猜出纸上的数。每猜一次第一位玩家都会给予第二位玩家相应的提示。若猜测的数字与纸上的数字有数码和位置均相同，记该数码为$A$类数码。若所猜数字与纸上数字有数码相同但位置不同，记该数码为$B$类数码。显然，提示由一对数字组成，表示$A$类数码和$B$类数码的数量。（所猜数字可以有重复）

更具体地，记纸上数字为$s$，玩家询问数字为$x$。$A$类数码的数量为对于某个位置$i(1<=i<=4)$使得$s[i]=x[i]$的$i$的数量。$B$类数码的数量为对于某两个位置$i,j(1<=i,j<=4)$使得$s[i]=x[j],i \neq j$的$i,j$的对数。

例如：纸上的数字为"0427"所猜的数字"0724"，则玩家一的提示为"2A2B"。其中，$A$类数码为"0","2"$B$类数码为"4","7"。

## 样例 #1

### 输入

```
0 1
2 0
1 1
0 4
2 1
4 0
```

### 输出

```
8000
0179
3159
3210
0112
0123```

# 题解

## 作者：封禁用户 (赞：3)

## 题解：CF753B Interactive Bulls and Cows (Easy)

### 题意简述

~~在这里吐槽一下题目说的不太清楚。~~

每次猜一个 $4$ 位字符串，回答为猜对多少位，猜错多少位。最多猜 $50$ 次。

### 解题思路

初看好像没什么思路。要是知道**这四位有什么**就好解决了。于是可以花 $10$ 次询问查询 $0$ 至 $9$ 每个数各出现了几次。然后花 $24$ 次搞**排列组合**就好了（这里我请出了万能的**桶**）。最坏情况使用 $34$ 次查询解决，满足题目要求。

坑点提醒：

- 在查询 $0$ 至 $9$ 每个数的个数时，如果输入 $4\ \ 0$，要及时停止。
- 使用 `endl` 而不是 `\n`，或加入 `flush(stdout);`（毕竟这是交互题）。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int num[20] , a , b;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i = 0 ; i <= 9 ; i++)
	{
		cout << i << i << i << i << endl;
		cin >> a >> b;
		if(a == 4)
		{
			return 0;
		}
		num[i] += a;
	}
	for(int i = 0 ; i <= 9 ; i++)
	{
		if(num[i])
		{
			num[i]--;
			for(int j = 0 ; j <= 9 ; j++)
			{
				if(num[j])
				{
					num[j]--;
					for(int k = 0 ; k <= 9 ; k++)
					{
						if(num[k])
						{
							num[k]--;
							for(int l = 0 ; l <= 9 ; l++)
							{
								if(num[l])
								{
									cout << i << j << k << l << endl;
									cin >> a >> b;
									if(a == 4)
									{
										return 0;
									}
								}
							}
							num[k]++;
						}
					}
					num[j]++;
				}
			}
			num[i]++;
		}
	}
	return 0;
}
```

---

## 作者：Bai_R_X (赞：1)

## 思路
我们首先统计 $0\sim9$ 出现的次数（统计 $[0000,1111,\cdots,9999]$ 的 $A+B$），按次数加入一个数组中。

然后再进行全排列（可以使用标准库提供的全排列函数 `next_permutation`），直至正确。
## 正确性分析
数字次数：$10$ 次。

全排列：最差 $4!=24$ 次。

$10+24=34<50$，所以可行。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,i,j;
vector<int> v;
signed main()
{
    for(i=0;i<10;i++)
    {
    	cout<<i<<i<<i<<i<<endl;
    	cin>>a>>b;
    	for(j=1;j<=a+b;j++)v.push_back(i);
	}
  //sort(v.begin(),v.end());
  //↑next_permutation函数需要排序，但因为我们是按数字顺序加入的vector，所以已经排好序了
	do
	{
        for(auto& it:v)cout<<it;
        cout<<endl;
        cin>>a>>b;
        if(a==4&&b==0)break;
    }while(next_permutation(v.begin(),v.end()));//全排列函数
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

数字版 Wordle Game。

给了 $50$ 次询问的限制，如此宽松，那自然去想一些不太动脑子的做法。

先询问 $\texttt{0000},\texttt{1111},\ldots,\texttt{9999}$，可以确定最终数字的组成。花费 $10$ 次。

然后枚举每一位可能填的值拿去询问，最坏情况需要花费 $4!=24$ 次。

所以照这样做最多只需要 $34$ 次。

# Code

```cpp
#include<bits/stdc++.h>
int a[10];
int main(){
	for(int i=0,x;i<=9;++i){
		putchar(i^48);putchar(i^48);putchar(i^48);putchar(i^48);putchar(10);fflush(stdout);
		scanf("%d%*d",&x);
		if(x==4)return 0;
		a[i]+=x;
	}
	for(int i=0;i<=9;++i)
	if(a[i]){
	--a[i];
	for(int j=0;j<=9;++j)
	if(a[j]){
	--a[j];
	for(int k=0;k<=9;++k)
	if(a[k]){
	--a[k];
	for(int l=0,x;l<=9;++l)
	if(a[l]){
		putchar(i^48);putchar(j^48);putchar(k^48);putchar(l^48);putchar(10);fflush(stdout);
		scanf("%d%*d",&x);
		if(x==4)return 0;
	}
	++a[k];
	}
	++a[j];
	}
	++a[i];
	}
	return 0;
}
```

---

## 作者：Starry___sky (赞：0)

这应该算是一个很脍炙人口的小游戏了吧 ~~（没玩过算我没说）~~

因为一共有 $50$ 次询问机会，那最简单直接的方法就不难想到。

我们把 $0 \sim9$ 全部询问一遍，如果回答两个整数不全为 $0$，说明答案数字里有这个数码，然后我们把这个数记下来。这就用了$10$次。

然后我们把这四个数的所有排列全部询问一遍，如果得到 $4,0$ 的回答就直接结束。最多需要 $4!=24$ 次，所以一共最坏只需要  $34$ 次完全没问题。

~~反正我小时候3次就猜出来了~~

### 小坑点：在第一遍询问0的时候要输出0000的字符串不能直接输出0！！！

&nbsp;

```cpp
#include<bits/stdc++.h>

using namespace std;

bool use[10];

int main()
{
    int a[10];
    memset(use, 1, sizeof(use));
    int cnt = 0;
    for(int i = 0; i <= 9; i++)//0~9全部询问
    {
        if(i != 0)
            cout << i * 1000 + i * 100 + i * 10 + i << endl;
        else
            cout << "0000" << endl;//这里要输出字符串
        int A, b;
        cin >> A >> b;
        if(A || b) //记录出现过的数字
            a[++cnt] = i, use[i] = 0;
    }
    int c, d;
    for(int i = 1; i <= cnt; i++)//暴力全排列
        for(int j = 1; j <= cnt; j++)
            for(int k = 1; k <= cnt; k++)
                for(int l = 1; l <= cnt; l++)
                {
                    if(i == j || i == k || i == l || j == k || j == l || k == l)
                        continue;
                    cout << a[i] << a[j] << a[k] << a[l] << endl;
                    int c, d;
                    cin >> c >> d;
                    if(c == 4)
                        return 0;
                }
    system("pause");
    return 0;
}
```

---

