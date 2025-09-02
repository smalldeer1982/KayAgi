# Boys and Girls

## 题目描述

There are $ n $ boys and $ m $ girls studying in the class. They should stand in a line so that boys and girls alternated there as much as possible. Let's assume that positions in the line are indexed from left to right by numbers from 1 to $ n+m $ . Then the number of integers $ i $ ( $ 1<=i&lt;n+m $ ) such that positions with indexes $ i $ and $ i+1 $ contain children of different genders (position $ i $ has a girl and position $ i+1 $ has a boy or vice versa) must be as large as possible.

Help the children and tell them how to form the line.

## 说明/提示

In the first sample another possible answer is BGBGBG.

In the second sample answer BBGBGB is also optimal.

## 样例 #1

### 输入

```
3 3
```

### 输出

```
GBGBGB
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
BGBGBB
```

# 题解

## 作者：Arvin2018 (赞：1)

~~话说明天阶段检测我咋还在写题解~~

这题真心神奇。。。竟然真要文件输入输出

我第一次不信邪结果TLE了

~~我还以为RemoteJudge万能呢~~
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);//这就是神奇所在
    int n, m;//n -> boy, m -> girl
    cin >> n >> m;
    if(n > m){//如果男生比女生多，那么女生就得被夹在中间，这样才能尽可能分开
        while(n&&m){//当n>0, m>0
            cout << "B";
            n--;
            cout << "G";
            m--;
        }
        while(n){n>0
            cout << "B";
            n--;
        }
    }
    else{
        while(n&&m){
            cout << "G";
            n--;
            cout << "B";
            m--;
        }//如果女生多就要把男生夹在中间
        while(m){
            cout << "G";
            m--;
        }
    }
    return 0;
}

```

---

## 作者：Daniel_yao (赞：0)

## 题目翻译

班上有 $n$ 名男生和 $m$ 名女生在学习。他们要站成一列，以便男孩和女孩交替出现。假设队列中同学的编号为 $1 \sim n+m$，那么我们要尽量让第 $i$ 名同学和第 $i+1$ 名同学性别不同（即第 $i$ 名为男生，$i+1$ 名为女生，反之亦可），也就是说我们要让这种情况出现次数最多。

### 具体思路

1. 处理男生和女生的边界；

2. 找出男女生的最小值，通过最小值来判断谁站在前面（若男生大于女生，则男生站到前面，反之女生站到最前面）；

3. 通过合理分配男女生的位置输出答案；

### 上代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<math.h>
#include<cstdio>
int main(){
	freopen("input.txt","r",stdin);//本题要求开文件输入输出。
	freopen("output.txt","w",stdout);
	int x, y;
	scanf("%d%d",&x, &y);//输入男生和女生的人数。
	int n = std::min(x, y);//取男女生的最小值。
	if(x < y){//如果男生人数小于女生人数，则让女生站前面。
		for(int i = 1; i <= n; i++){//处理男女生边界。
			printf("GB");
		}
		for(int i = 1; i <= y - n; i++){//让女生站前面。
			printf("G");
		}
	}
	else{//反之，男生站前面；
		for(int i = 1; i <= n; i++){//处理男女生边界。
			printf("BG");
		}
		for(int i = 1; i <= x - n; i++){//让男生站前面。
			printf("B");
		}
	}
	return 0;
}
```


---

## 作者：Colead (赞：0)

又是一道要写文件的 CF 题。

想法非常简单，基本贪心，先让男女生交替站立，多出来的嘛，全站最后。

既然有了这种想法，就只剩最后一个细节要处理了。就是合理排序（交替站）和不合理排序（最后排不下的一堆人）的交界处。

应该让他也成为交界。

所以男生多第一个站男生，女生多第一个站女生。

别忘写文件！

```
#include<bits/stdc++.h>
using namespace std;
long long a,b;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>a>>b;
	if(a>=b)
	{
		for(int i=1;i<=min(a,b);i++)
		{
			cout<<"BG";
		}
		for(int i=1;i<=a-min(a,b);i++)
		{
			cout<<"B";
		}
	}
	else
	{
		for(int i=1;i<=min(a,b);i++)
		{
			cout<<"GB";
		}
		for(int i=1;i<=b-min(a,b);i++)
		{
			cout<<"G";
		}
	}
	return 0;
}
```


---

## 作者：_easy_ (赞：0)

# 思路
直接输出 $\min(m,n)$ 个 $\texttt{GB}$ 或 $\texttt{BG}$ 就行了，注意一下文件输入输出。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m; 
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);//文件输入输出
	cin>>n>>m;
	if(n<=m){
		for(int i=1;i<=n;i++){
			cout<<"GB";
		}//n个GB
		m-=n;
		for(int i=1;i<=m;i++){
			cout<<"G";
		}//剩下的用G填充
	}else{
		for(int i=1;i<=m;i++){
			cout<<"BG";
		}//m个BG
		n-=m;
		for(int i=1;i<=n;i++){
			cout<<"B";
		}//剩下的用B填充
	}
	return 0;
}


```

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个男生、$m$ 个女生坐在一排，请求出这样一种方案，使得相邻两个座位之间的人的性别不同的次数最多。

**数据范围：$1\leqslant n,m\leqslant 100$。**
## Solution
这题不难，就是先把能男女组合的尽量组合了，然后剩余有多的直接丢在后面不管（或者也可以先把多的求出来然后丢在前面，但是不如本方法方便，读者可以亲自尝试），但是有坑点：

1. 这题目要开文件输入输出！所以千万不要忘了 $\texttt{freopen}$。
2. 如果是女生多，则两两组合时先让女生在前，男生在后，这样才能尽可能地满足题目要求。如果是男生多，则两两组合时先让男生在前，女生在后。

跳过这些坑点，胜利其实就在眼前了。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int n, m, minx;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout); 
	scanf("%d%d", &n, &m);
	minx = min(n, m);
	for(int i = 1; i <= minx; ++i)	
		printf(minx == n ? "GB" : "BG");
	n -= minx, m -= minx;
	if(n)	for(int i = 1; i <= n; ++i)	printf("B");
	else	for(int i = 1; i <= m; ++i)	printf("G");
	return 0;
}
```

---

## 作者：ZolaWatle (赞：0)

### CF253A 题解

基本思路：分三种情况讨论，按照题意模拟即可。

------------

1. 男女生一样多：直接无脑“BGBG”或者“GBGB”就行了，样例给的是“GBGB”，于是我使用的是这个。

2. 男生比女生多：循环输出“BG”，次数是女生的人数。再循环输出“B”，此数是男生人数 $ - $ 女生人数。

------------

- 那为什么不循环输出“GB”呢？因为男多女少，循环输出的最后一个字母是“G”，下一个肯定是“B”，又会有一个“GB”的串。

------------

3. 女生比男生多，同上之理：循环输出“GB”，次数是女生的人数。再循环输出“G”，此数是女生人数 $ - $ 男生人数。

好了，现在思路已经谈完了，请**看代码**：

------------

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define re register int
using namespace std;

int n,m,k;
string ans[2]={"BG","GB"};  //用string类型比较方便输出答案 

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	std::scanf("%d%d",&n,&m);
	if(n==m)
	{
		for(re i=1;i<=n;i++)
			std::cout<<"GB";
		return 0;
	}
	if(n>m)
	{
		k=0;
		for(re i=1;i<=m;i++)
			std::cout<<ans[k];
		n-=m;
		for(re i=1;i<=n;i++)
			std::cout<<"B";
		return 0;
	}
	if(n<m)
	{
		k=1;
		for(re i=1;i<=n;i++)
			std::cout<<ans[k];
		m-=n;
		for(re i=1;i<=m;i++)
			std::cout<<"G";
		return 0;
	}//分三种情况讨论~ 
}
```


---

