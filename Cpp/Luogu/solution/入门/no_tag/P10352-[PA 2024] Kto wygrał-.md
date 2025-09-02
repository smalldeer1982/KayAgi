# [PA 2024] Kto wygrał?

## 题目背景

PA 2024 1C

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 1 [Kto wygrał?](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/kto/)**

Algosia 和 Bytie 喜欢在 PA 中一较高下。在线上比赛中，有 $18$ 道题需要解决，每道题可获得 $0$ 到 $10$ 分。参赛者按总得分排序。如果积分相同，则在更多题中获得 $10$ 分的选手排名靠前。如果再次出现同分情况，则在更多题中获得 $9$ 分的选手排名靠前，依此类推。如果无法通过这种方式区分选手，则宣布他们之间打成平手。

Algosia 和 Bajtek 还记得上届比赛所有任务的得分，但他们不记得……谁赢了。你能帮他们编写一个程序，读取他们的成绩，并告诉他们谁的名次更高吗？

## 说明/提示

虽然 Algosia 和 Bytie 的得分都是 $161$ 分，但根据 PA 规则，Algosia 的排名更高。

## 样例 #1

### 输入

```
10 10 7 10 10 10 10 10 10 10 10 10 0 10 4 10 10 10
10 10 10 10 10 10 10 10 10 10 10 10 4 3 4 10 10 10
```

### 输出

```
Algosia
```

# 题解

## 作者：Mierstan085 (赞：5)

这是一道 PA 难得的简单题。

思路是先计算两个人的成绩和，然后开一个桶数组来分别记录两个人同样分数的题目的个数。

然后先比较成绩和，在从 $10$ 开始到 $0$ 比有没有不同的，如果桶数组没有一个不同，就输出 `remis`，然后就根据情况输出 `Algosia` 和 `Bajtek`（上文名字是 Bysie，下文变了）。

代码是这样的：
```cpp
#include <bits/stdc++.h>
using namespace std;

int cnt[2][20], a[2];
int main(){
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 18; j ++){
            int x;
            cin >> x;
            cnt[i][x] ++;
            a[i] += x;
        }
    }
    
    if (a[0] == a[1]){
        for (int i = 10; i >= 0; i --){
            if (cnt[0][i] != cnt[1][i]){
                if (cnt[0][i] > cnt[1][i]){
                    cout << "Algosia";
                    return 0;
                }else{
                    cout << "Bajtek";
                    return 0;
                }
            }
        }
        
        cout << "remis";
    }else{
        if (a[0] > a[1]) cout << "Algosia";
        else cout << "Bajtek";
    }
}
```

完结撒花~

---

## 作者：yu1128_AKIOI (赞：1)

# 思路

按题意模拟即可。数清两个人得到各个分数的次数，最后从 10 分枚举到 0 分，若 Algosia 多，则输出 ```Algosia```，反之输出 ```Bajtek```；若全部相等，输出 ```remis```。

# 代码

```cpp
#include<iostream>
using namespace std;
int ans1,ans2,a[12],b[12];
int main(){
    for(int i=1;i<=18;i++){
        int x;
        cin>>x;
        a[x]++;
        ans1+=x;
    }
    for(int i=1;i<=18;i++){
        int x;
        cin>>x;
        b[x]++;
        ans2+=x;
    }
    if(ans1>ans2) cout<<"Algosia";
    else if(ans1<ans2) cout<<"Bajtek";
    else{
        for(int i=10;i>=0;i--){
            if(a[i]>b[i]){
                cout<<"Algosia";
                return 0;
            }
            else if(a[i]<b[i]){
                cout<<"Bajtek";
                return 0;
            }
        }
        cout<<"remis";
    }
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 分析
红色大模拟。
## 解法
### 求总分
全部相加即可。
### 总分不等
比大小输出即可。
### 总分相等
按题目要求比：比十分个数，九分，八分，以此类推。
### 啥都一样
输出平局。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11],b[11],as,bs;
int main(){
    for(int i=1,t;i<=18;i++){
        cin>>t;
        a[t]++;
        as+=t;
    }
    for(int i=1,t;i<=18;i++){
        cin>>t;
        b[t]++;//计数
        bs+=t;//求总分
    }//输入
    bool f=0;
    if(as>bs){f=1;cout<<"Algosia";}
    else if(bs>as){f=1;cout<<"Bajtek";}//比总分
    else{//总分相等
        for(int i=10;i>=1;i--){
            f=1;
            if(a[i]>b[i])cout<<"Algosia";
            else if(b[i]>a[i])cout<<"Bajtek";//比个数
            if(a[i]==b[i])f=0;
            if(a[i]!=b[i])break;
        }
        if(!f)cout<<"remis";//全相等
    }
    return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
先把 Algosia 和 Bytie 的总分记录下来，然后再记录 Algosia 和 Bytie 的分数中 $0 \sim 10$ 出现的次数，然后按照题目意思做：
- 先比较 Algosia 和 Bytie 的总分，如果 Algosia 的总分比 Bytie 的总分小，输出 `Algosia`，结束程序。如果 Bytie 的总分比 Algosia 的总分小，输出 `Bytie`，结束程序。
- 接下来处理 Algosia 和 Bytie 的总分相同的情况。从大到小遍历 Algosia 和 Bytie 的分数中 $0 \sim 10$ 出现的次数，如果两个人的数字出现次数不一样，则输出，并结束程序。
- 如果到这里程序还没有结束，则输出 `remis`，表示平局。
### 代码
```cpp
#include<deque>
#include<stack>
#include<queue>
#include<cmath>
#include<vector>
#include<climits>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#define il inline
#define ll long long
const ll mod=1e9+7;
const ll inf=0x3f3f3f3f;
const double pi=acos(-1.0);
const double Exp=1e-8;
il int read(){
 int x=0,t=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
 return x*t;
}
il void write(int x){
 if(x<0){putchar('-');x=-x;}
 if(x>9)write(x/10);
 putchar(x%10+'0');
}
#define N 15
int t[N],t1[N],x,ans1,ans2; 
int main(){
	for(int i=0;i<18;i++)std::cin>>x,t[x]++,ans1+=x;
	for(int i=0;i<18;i++)std::cin>>x,t1[x]++,ans2+=x;
	if(ans1<ans2)puts("Bajtek"),exit(0);
	if(ans1>ans2)puts("Algosia"),exit(0);
	for(int i=10;i>=0;i--){
		if(t[i]>t1[i])puts("Algosia"),exit(0);
		if(t[i]<t1[i])puts("Bajtek"),exit(0);
	}
	puts("remis");
}
```

---

## 作者：we_are_the_chuibing (赞：0)

先将每个人的分数求和，如两个人的分数不同则比较后直接输出谁赢，相同则再统计一下每个人得每个分数的次数，从大到小一个个比较，如有不同直接判断输出，最后全部相同就返回平局。

```cpp
#include<iostream>
using namespace std;
long long a[19],b[19],aa[19],bb[19],ans1,ans2;
int main(){
	for(int i=1;i<=18;i++){
		cin>>a[i];ans1+=a[i];aa[a[i]]++;
	}
	for(int i=1;i<=18;i++){
		cin>>b[i];ans2+=b[i];bb[b[i]]++;
	}
	if(ans1>ans2){cout<<"Algosia";return 0;}
	if(ans1<ans2){cout<<"Bajtek";return 0;}
	for(int i=10;i>=0;i--){
		if(aa[i]>bb[i]){cout<<"Algosia";return 0;}
		if(aa[i]<bb[i]){cout<<"Bajtek";return 0;}
	}
	cout<<"remis";
	return 0;
}
```

---

## 作者：suyi1111 (赞：0)

让我们分三步解决这道题目

第一步：求出总和

```
	int a[20],b[20],n=18,suma=0,sumb=0;
	//数组a是指Algosia每道题目的得分，数组b是指Bajtek每道题目的得分
	//suma是指a的总分，sumb是指b的总分
	for(int i=1;i<=n;i++){
		cin>>a[i];suma+=a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];sumb+=b[i];
	}
	if(suma<sumb){
		cout<<"Bajtek";
		return 0;
	}
	if(sumb<suma){
		cout<<"Algosia";
		return 0;
	}
```
第二步，通过题目中所说的第二种方法来计算排名：
```
int ha[20],hb[20];
	memset(ha,0,sizeof(ha));
	memset(hb,0,sizeof(hb));//清空数组 
	for(int i=1;i<=n;i++){
		ha[a[i]]++;//ha[i]表示Algosia有ha[i]道题目的得分是i
		hb[b[i]]++;//hb[i]表示Bajtek有hb[i]道题目的得分是i
	}
	for(int i=10;i>=0;i--){
		if(ha[i]>hb[i]){
			cout<<"Algosia";//Algosia赢 
			return 0;
		}else if(hb[i]>ha[i]){
			cout<<"Bajtek";//Bajtek赢 
			return 0;
		}
	}
```
最后一步，判平局
```
	cout<<"remis"; 
```
完整代码：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a[20],b[20],n=18,suma=0,sumb=0;
	//数组a是指Algosia每道题目的得分，数组b是指Bajtek每道题目的得分
	//suma是指a的总分，sumb是指b的总分
	for(int i=1;i<=n;i++){
		cin>>a[i];suma+=a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];sumb+=b[i];
	}
	if(suma<sumb){
		cout<<"Bajtek";
		return 0;
	}
	if(sumb<suma){
		cout<<"Algosia";
		return 0;
	}
	int ha[20],hb[20];
	memset(ha,0,sizeof(ha));
	memset(hb,0,sizeof(hb));//清空数组 
	for(int i=1;i<=n;i++){
		ha[a[i]]++;//ha[i]表示Algosia有ha[i]道题目的得分是i
		hb[b[i]]++;//hb[i]表示Bajtek有hb[i]道题目的得分是i
	}
	for(int i=10;i>=0;i--){
		if(ha[i]>hb[i]){
			cout<<"Algosia";//Algosia赢 
			return 0;
		}else if(hb[i]>ha[i]){
			cout<<"Bajtek";//Bajtek赢 
			return 0;
		}
	}
	cout<<"remis"; 
	return 0;
}
```

---

## 作者：_Warfarin_ (赞：0)

### 分析
~~非常简单，根据题意模拟即可。~~   
读入时，求和。先比较总分的大小。然后排个序，从大的一端开始比较，谁比较大，谁获胜。

### AC 代码
```

#include <bits/stdc++.h>

#define ll long long
#define io cin.tie(0),cout.tie(0),ios::sync_with_stdio(false)
#define ri register int
#define lb long double

using namespace std;
const int N = 114514;
int a[N], b[N];
int tot_a = 0, tot_b = 0;
inline void  solve()
{
	sort(a + 1, a + 1 + 18);
	sort(b + 1, b + 1 + 18);
	if (tot_a > tot_b)
	{
		cout << "Algosia" << endl;
		return ;
	}
	if (tot_a < tot_b)
	{
		cout << "Bajtek" << endl;
		return ;
	}
	for (ri i = 18; i >= 1; i--)
	{
		if (a[i] > b[i])
		{
			cout << "Algosia" << endl;
			return ;
		}
		if (a[i] < b[i])
		{
			cout << "Bajtek" << endl;
			return ;
		}
	}
	cout << "remis" << endl;
}

int main()
{
	io;
	for (ri i = 1; i <= 18; i++)
	{
		cin >> a[i];
		tot_a += a[i];
	}
	for (ri i = 1; i <= 18; i++)
	{
		cin >> b[i];
		tot_b += b[i];
	}
	solve();
	return 0;
}

```

---

## 作者：sillation (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10352)

------------
### 题解：P10352 [PA2024] Kto wygrał?题解
一道适合初学者的题。

本题你需要用到【循环】，【排序】，【条件判断】等知识点。其中【排序】你可以使用最简单的计数排序。



------------

#### 思路：
根据题目所描述，我们可以建立两个桶数组 $f$ 和 $t$，用来记录两人每种分值有多少道题。用变量 $a$ 输入。$sum$ 和 $sumb$ 记录两人的总分。


循环输入每人每道题的分值，注意每人循环输入的数量是固定的。记录分值。然后判断，若总分相等，则从十到零依次用桶数组判断每人每种分值对的数量。若相等则继续判断，否则输出多的那个人。若总分不相等，输出总分大的人。若打成平手，则输出 `remis`。

注意，只要输出了就一定要结束程序。


------------
#### code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[20]={0},a,sum,sumb,f[20]={0}; 
int main(){
	for(int i=1;i<=18;i++) cin>>a,sum+=a,t[a]++;
	for(int i=1;i<=18;i++) cin>>a,sumb+=a,f[a]++;
	if(sum==sumb){
		for(int i=10;i>=1;i--){
			if(t[i]>f[i]){
				cout<<"Algosia";
				return 0;
			}
			else if(t[i]<f[i]){
				cout<<"Bajtek";
				return 0;
			}
		}
	}
	else{
		if(sum>sumb) cout<<"Algosia";
		else cout<<"Bajtek";
		return 0;
	}
	cout<<"remis";
	return 0;
}

```

笔者的码风不太好，还望读者见谅。

---

