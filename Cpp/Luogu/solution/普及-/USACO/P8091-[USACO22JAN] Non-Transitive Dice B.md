# [USACO22JAN] Non-Transitive Dice B

## 题目描述

为了消磨牛棚里的时光，奶牛们喜欢玩简单的骰子游戏。其中一种游戏使用两个骰子 X 和 Y 进行。两个骰子均被投掷，获胜的骰子是显示的数字较大的骰子。如果两者显示相同的数字，则重新投掷（只要持续打平，骰子可能会被重新投掷多次）。我们称骰子 X 击败骰子 Y，如果骰子 X 比骰子 Y 更有可能赢得这局游戏。

考虑以下的 $4$ 面骰子：

骰子 A 在各面上有数字 $4$，$5$，$6$ 和 $7$。

骰子 B 在各面上有数字 $2$，$4$，$5$ 和 $10$。

骰子 C 在各面上有数字 $1$，$4$，$8$ 和 $9$。

这些骰子满足一个相当奇妙的性质：A 击败 B，B 击败 C，并且 C 也击败 A。特别地，三个骰子都不是「最佳的」，可以击败其他两个。在这种情况下，当没有两个骰子打平，也没有一个骰子是最佳的，我们称这三个骰子的集合为「非传递的」。在非传递的三个骰子的集合中，每个骰子击败一个其他骰子，并输给另一个其他骰子。

给定两个 $4$ 面骰子 A 和 B 各面上的数字，请帮助奶牛们求出是否有方法为第三个骰子 C 的各面分配数字，使得这个骰子的集合是非传递的。所有骰子面上的数字必须是 $1$ 到 $10$ 的整数。

## 说明/提示

**【样例解释】**

第一个子测试用例对应题目中的例子。在第二个子测试用例中，不存在骰子 C 可以使得这个骰子集合是非传递的。同理第三个子测试用例的答案也是 `no`。



## 样例 #1

### 输入

```
3
4 5 6 7 2 4 5 10
2 2 2 2 1 1 1 1
1 1 1 1 2 2 2 2```

### 输出

```
yes
no
no```

# 题解

## 作者：清小秋ovo (赞：12)

# USACO 铜组 T2 题解

看到数据立马暴力。

因为筛子只有 $4$ 面，且每面数字最大为 $10$。

哪怕是 $O(n ^4)$ 的复杂度也无伤大雅。

## 题意

当 $A$ 筛 赢 $B$ 筛的可能性更大时，则需满足： $B$ 筛赢 $C$ 筛可能性更大，且 $C$ 筛赢 $A$ 筛可能性更大。

反之，当 $B$ 赢 $A$ 时，则需满足 $C$ 赢 $B$, $A$ 赢 $C$。

## 代码

$15$ 分钟乱打的。可能码风有点丑。直接四层循环模拟 + 判断。

结构比较清晰，可以对上刚刚解释的思路，所以就不放注释了。

```cpp
#include<bits/stdc++.h>

using namespace std;

int T, a[4],b[4],c[4];

inline int read()
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
    return f * x;
}

bool x_win_y(int x[4], int y[4]){
    int x_cnt =0, y_cnt = 0; 
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(x[i]>y[j])x_cnt++;
            else if(x[i]<y[j])y_cnt++;
        }
    }
    return x_cnt > y_cnt;
}

bool check(){
    if(x_win_y(a,b) && x_win_y(b,c) && x_win_y(c,a))return true;
    if(x_win_y(b,a) && x_win_y(c,b) && x_win_y(a,c))return true;
    return false; 
}

void solve(){

    for(c[0]=1;c[0]<=10;c[0]++){
        for(c[1]=c[0];c[1]<=10;c[1]++){
            for(c[2]=c[1];c[2]<=10;c[2]++){
                for(c[3]=c[2];c[3]<=10;c[3]++){
                    if(check()){
                        puts("yes"); 
                        return;
                    }
                }
            }
        }
    }
    puts("no");
}

int main()
{
    T = read();
    while(T--){
        for(int i=0;i<4;i++) a[i] = read();
        for(int i=0;i<4;i++) b[i] = read();
        solve();
    }
   return 0;
}
```


---

## 作者：yeshubo_qwq (赞：5)

## 思路
先特判，如果 $a$ 和 $b$ 平局直接输出 `no`。

否则让 $a$ 为赢的，$b$ 为输的，方便判断。

然后搜索求出 $c$ 的全排列，对每一个都进行判断，看看有没有符合要求的。

~~再然后，就可以愉快的 AC 了。~~
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,i,flag,a[5],b[5],c[5];
int check(int *a,int *b){
//判断a，b的胜负（1为a胜，0为平局，-1为a败）
	int w=0,l=0;
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			if(a[i]>b[j])w++;
			else if(a[i]<b[j])l++;
	if(w>l)  return  1;
	if(w<l)  return -1;
	if(w==l) return  0;
}
void dfs(int t){
	if(flag==1)return;//有一种方案即可
	if(t>4){
		if(check(a,c)==-1&&check(b,c)==1)//符合要求
			flag=1;//标记
		return;
	}
	for(int i=1;i<=10;i++)c[t]=i,dfs(t+1);
}
int main(){
	scanf("%d",&T);
	while(T--){
		for(i=1;i<=4;i++)scanf("%d",&a[i]);
		for(i=1;i<=4;i++)scanf("%d",&b[i]);
		int x=check(a,b);
		if(x==0){printf("no\n");continue;}//特判平局
		if(x==-1)swap(a,b);//让a为赢，b为输
		flag=0;//默认没有合法方案
		dfs(1);//搜索全排列
		flag==1?printf("yes\n"):printf("no\n");
	}
	return 0;
}
```


---

## 作者：SunSkydp (赞：4)

[可能会有更好的阅读体验](https://www.cnblogs.com/sunskydp/p/solution-p8091.html)

直接模拟就好了（~~暴力出奇迹~~）。

因为不知道是 $A$ 击败 $B$ 还是 $B$ 击败 $A$，所以只要判断 chck 函数的结果是否相等（相等即为「非传递的」）就行了。

然后注意要先排序。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T, a[5], b[5], c[5];
bool flag = false;
int chck(int m[], int n[]) {
	int s1 = 0, s2 = 0;
	for(int i = 1; i <= 4; i++) 
	    for(int j = 1; j <= 4; j++)
	        if(m[i] > n[j]) s1++;
	        else if(m[i] < n[j]) s2++;
	if(s1 == s2) return -1;
	else return s1 > s2 ? 1 : 0;
}
int main() {
	scanf("%d", &T);
	while(T--) {
		flag = false; 
		for(int i = 1; i <= 4; i++) cin >> a[i];
        for(int i = 1; i <= 4; i++) cin >> b[i];
		sort(a + 1, a + 5);
		sort(b + 1, b + 5);
		for(c[1] = 1; c[1] <= 10; c[1]++) 
		for(c[2] = 1; c[2] <= 10; c[2]++)
		for(c[3] = 1; c[3] <= 10; c[3]++) 
		for(c[4] = 1; c[4] <= 10; c[4]++){
			int aa = chck(a, b), bb = chck(c, a), cc = chck(b, c);
			if(aa == bb && bb == cc && aa != -1 && bb != -1 && cc != -1) {
				flag = true;
				break;
			}
		}
		if(flag) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}

```

---

## 作者：ztlh (赞：3)

~~**数据真氵**~~

考场上想优化想了好久，最后发现**暴力**就能过。

### My Solution：

每组数据输入后，先用两个变量 $win$ 和 $lose$ 辅助计数输入两组的输赢情况，如有**平局**则**直接输出 no** 并进行下一轮询问。

若 $A$ 输给 $B$，则交换两个数组，随后**四重循环暴力搜索+判断**，如有合法情况，**标记**并**退出循环**。最后依据标记输出结果。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int a[5];
int b[5];
int c[5];
int main(){
	scanf("%d",&T);
	while(T--){
		for(int i=1;i<=4;i++) scanf("%d",&a[i]);
		for(int i=1;i<=4;i++) scanf("%d",&b[i]);
		int win=0,lose=0;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
				if(a[i]>b[j]) win++;
				else if(a[i]<b[j]) lose++;
		if(win==lose){ //处理打平
			printf("no\n");
			continue;
		}
		bool flag=0;
		sort(a+1,a+5);sort(b+1,b+5);
		if(win<lose) swap(a,b);
		for(c[1]=1;c[1]<=10;c[1]++){
			for(c[2]=c[1];c[2]<=10;c[2]++){
				for(c[3]=c[2];c[3]<=10;c[3]++){
					for(c[4]=c[3];c[4]<=10;c[4]++){
						bool f1=1;
						int w1=0,l1=0,w2=0,l2=0;
						for(int i=1;i<=4;i++)
							for(int j=1;j<=4;j++){
								if(a[i]>c[j]) w1++;
								else if(a[i]<c[j]) l1++;
								if(b[i]>c[j]) w2++;
								else if(b[i]<c[j]) l2++;
							}
						if(w1<l1&&w2>l2){
							printf("yes\n");
							flag=1;
							break;
						}
					}
					if(flag) break;
				}
				if(flag) break;
			}
			if(flag) break;
		}
		if(!flag) printf("no\n");
	}
	return 0;
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：2)

因为题面上写了“所有骰子面上的数字必须是 $1$ 到 $10$ 的整数”，而且骰子只有4面因此考虑爆搜，时间复杂度最多 $\Theta(10^4)$。

实现起来也很简单，对于每个面上的数字都枚举一遍 $1$ 到 $10$，每一种枚举情况都尝试能不能击败骰子 A，而且被骰子 B 击败。至于如何判断骰子 X 是否击败骰子 Y，可以用这样一个函数：
```cpp
bool jibai(int a[],int b[]){//判断骰子A能不能击败骰子B
	int tot=0;//计算胜利可能数
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(a[i]>b[j]) tot++;//记录
			if(a[i]<b[j]) tot--;
		}
	}
	return tot>0;//A击败了B
}
```
不过主函数里还需要注意一些细节。最后上整体代码：
```cpp
#include<iostream>
using namespace std;
int a[5],b[5];//输入a和b
bool jibai(int a[],int b[]){//刚才的击败函数
	int tot=0;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(a[i]>b[j]) tot++;
			if(a[i]<b[j]) tot--;
		}
	}
	return tot>0;
}
int c[5],ans;
void dfs(int now){//暴力枚举
	if(now>4){//一种可能
		if(jibai(b,c)&&jibai(c,a)) ans++;//如果没问题，就算上答案的一种
		return;
	}
	for(int i=1;i<=10;i++){//从1到10尝试
		c[now]=i;
		dfs(now+1);
	}
	return;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		ans=0;
		cin>>a[1]>>a[2]>>a[3]>>a[4]>>b[1]>>b[2]>>b[3]>>b[4];//输入
		if(jibai(b,a)){//让a一定能击败b
			swap(a[1],b[1]);swap(a[2],b[2]);swap(a[3],b[3]);swap(a[4],b[4]);
		}
		if(!jibai(a,b)){//在a一定能击败b的时候a没法击败b，就是平局(这句有点绕，自行理解，上一个a一定能击败b其实指的是不会被b击败)
			cout<<"no"<<endl;
			continue;
		}
		dfs(1);//暴力枚举
		if(ans) cout<<"yes"<<endl;
		else cout<<"no"<<endl; 
	}
	return 0;
}

```

---

## 作者：Jerrlee✅ (赞：2)

## 题意
给出两个骰子 `X` 和 `Y`，如果 `X` 大于 `Y` 的可能性更大，那么认为骰子 `X` 更有可能赢得这局游戏。

如果 `A` 能打败 `B`，`B` 能打败 `C`，`C` 又能打败 `A`，那么我们称这三个骰子的集合为「非传递的」。

给出 $t$ 组数据，判断是否有骰子 `C` 与给出的骰子 `A`，`B` 满足非传递性。

注意，给出的 $8$ 个数字可能分别属于骰子 `A` 和 `B`，也可能分别属于骰子 `B` 和 `A`！
## 思路
$t \leq 10$，每次只有 $8$ 个数，数又在 $1 \sim 10$ 之间，可以考虑暴力。

依次从 $1 \sim 10$ 枚举骰子 `C`，判断是否与前两个骰子满足非传递性即可。

为了简洁，如果先给的骰子败给了后给的骰子，那么交换他俩，这样只需要看后一个骰子能否打败骰子 `C`，骰子 `C` 能否打败前一个骰子就够了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int fun(int a[],int b[]){
    int cnt=0;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(a[i]>b[j]) cnt++;
            if(a[i]<b[j]) cnt--;
        }
    }
    if(cnt>0) return 1;
    else return 0;
}
signed main(){
    cin>>t;
    while(t--){
        if(0){
            be:
            continue;
        }
        int a[9],b[9];
        for(int i=1;i<=4;i++) cin>>a[i];
        for(int i=1;i<=4;i++) cin>>b[i];
        if(fun(b,a))
            for(int i=1;i<=4;i++) swap(a[i],b[i]);
        for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                for(int k=1;k<=10;k++){
                    for(int l=1;l<=10;l++){
                        int c[9]={0,i,j,k,l};
                        if(fun(b,c)&&fun(c,a)){cout<<"yes\n";goto be;}//懒得开个 flag 记录了，就用了 goto，因为 if(0) 永远不会进入，我们 goto 是本程序中唯一可以进入这个判断语句的方法，所以直接 continue 不会有问题。
                    }
                }
            }
        }
        cout<<"no\n";
    }
}
```
[AC 记录（洛谷）](https://www.luogu.com.cn/record/68526019)

---

## 作者：RootMirzayanov (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P8091)

## 题意

给定两个四面骰子 $A, B$ 及每一面的点数 $A:\{A_1,A_2,A_3,A_4\}, B:\{B_1,B_2,B_3,B_4\}$。

您需要求出是否存在一个四面骰子 $C:\{C_1,C_2,C_3,C_4\}$，使得 $A,B,C$ 三个骰子之间不存在两个骰子获胜的概率相同，也不存在一个骰子能够同时比另外两个骰子有更高概率获胜。

## 解析

由于 $A,B,C$ 每一面的点数都不大于 $10$, 所以以 $\mathcal{O(n^4)}$ 的时间复杂度暴力枚举所有可能的 $C:\{C_1,C_2,C_3,C_4\}$ 是不会 `TLE` 的。我们可以创建一个 `bool` 类型的变量 `flag` 用来存储是否有符合条件的骰子 $C$, 并在处理每组数据开始前初始化为 `false`, 如果枚举到符合条件的 $C$ 则将 `flag` 的值改为 `true`。

需要注意的是，因为 $A,B,C$ 每面的点数**无序**，所以我们需要构造 $A^3_3=6$ 种有序环去判断是否符合条件，如果任意一种环是符合条件的，则 $C$ 是符合条件的。

---

## 作者：Ginger_he (赞：1)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/15864339.html)
# 题目描述
给定两个四面骰子 $A$ 和 $B$，且骰子上的数均在 $1$ 和 $10$ 之间。问是否存在骰子 $C$，使得三个骰子的胜负关系形成一个环。
# 题解
直接暴力枚举 $C$ 上的数即可，不要忘了有**平局**的情况。
## 小优化
1. 如果存在一种情况满足条件就不用继续枚举了；
2. 由于 $1,2,4,5$ 和 $1,5,2,4$ 是一样的，所以我们可以把 $C$ 当作一个单调不降的序列来枚举，即 $c_i\ge c_{i-1}$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,a[5],b[5],c[5],ans;
int cmp(int *x,int *y)
{
	int p=0,q=0;
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
		{
			if(x[i]>y[j]) p++;
			if(x[i]<y[j]) q++;
		}
	}
	if(p>q) return 1;//x胜
	if(p<q) return -1;//y胜
	return 0;//平局
}
void dfs(int x,int y)
{
	if(ans)
		return;//已经有答案就不用继续找了
	if(x==5)
	{
		int res=k+cmp(b,c)+cmp(c,a);
		ans|=(res==3||res==-3);
		/*
		a->b,b->c,c->a
		b->a,a->c,c->b
		*/ 
		return;
	}
	for(int i=y;i<=10;i++)
		dfs(x+1,c[x]=i);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		for(int i=1;i<=4;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+5);
		for(int i=1;i<=4;i++)
			scanf("%d",&b[i]);
		sort(b+1,b+5);
		k=cmp(a,b);
		if(!k)
		{
			printf("no\n");
			continue; 
		}//平局不符合条件
		dfs(1,1);//枚举c的四个数
		printf("%s\n",ans?"yes":"no");
	}
	return 0;
}
```

---

## 作者：fz20181223 (赞：0)

发现骰子只有 $4$ 个面，每个面只可能是 $[1,10]$ 间的数字，也就是说，一个骰子只有 $10^{4}$ 种可能的形态。

所以我们完全可以通过暴力枚举第三个骰子每面的数值，并与另外两个比较关系。

复杂度 $O(n^{2}2k^{n})$ 级别，其中 $n$ 为骰子面数，$k$ 为每面可能的数值数，由于 $n$ 和 $k$ 都很小，故完全没有压力。

考场源代码（有删改）：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct dice{
	int a[4];
	bool operator <(dice b){
		int t1=0,t2=0;
		dice &a=*this;
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j){
				t1+=a.a[i]>b.a[j];
				t2+=a.a[i]<b.a[j];
			}
		}
		return t1<t2;
	}
	bool operator >(dice b){
		int t1=0,t2=0;
		dice &a=*this;
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j){
				t1+=a.a[i]>b.a[j];
				t2+=a.a[i]<b.a[j];
			}
		}
		return t1>t2;
	}
}a,b,c;
void solve(){
	for(int i=0;i<4;++i)scanf("%d",&a.a[i]);
	for(int i=0;i<4;++i)scanf("%d",&b.a[i]);
	for(c.a[0]=1;c.a[0]<=10;++c.a[0]){
		for(c.a[1]=1;c.a[1]<=10;++c.a[1]){
			for(c.a[2]=1;c.a[2]<=10;++c.a[2]){
				for(c.a[3]=1;c.a[3]<=10;++c.a[3]){
					bool f=0;
					if(a>b&&b>c&&c>a)f=1;
					if(a<b&&b<c&&c<a)f=1;
					if(f){
						printf("yes\n");
						return;
					}
				}
			}
		}
	}
	printf("no\n");
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;}
```

---

## 作者：lsj2009 (赞：0)

## 题目大意
给定两个长为 $4$，有且仅有 $1$ 至 $10$ 的正整数序列 $A$ 与 $B$，****称 $A$ 击败 $B$ 为每个 $A_i>B_j$ 的次数比 $B_j>A_i$ 的次数多****。问是否存在一个长为 $4$，有且仅有 $1$ 至 $10$ 的序列 $C$ 满足：没有一个序列可以同时击败另外两个序列。
## 思路
~~没想到当 CSP-J2 考模拟时，USACO Cu 却爱上了暴力。~~

很简单直接枚举序列 $C$，然后判断每个序列 $C$ 是否满足条件即可。

code 如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],b[5],T;
bool AwinB(int A[],int B[]) { //判断序列 A 是否击败序列 B
	int win=0,lose=0;
	for(int i=1;i<=4;i++)
	    for(int j=1;j<=4;j++){
	        if(A[i]>B[j]) ++win; //A[i] 胜过 B[j] 的次数+1
	        if(A[i]<B[j]) ++lose; //B[j] 胜过 A[i] 的次数+1
	    }
    return win>lose;
}
bool check() {
	for(int i=1;i<=10;i++) //枚举 C序列的每一个元素
    	for(int j=1;j<=10;j++)
        	for(int k=1;k<=10;k++)
            	for(int l=1;l<=10;l++) {
                	int c[5]={0,i,j,k,l};
					if((AwinB(a,b)&&AwinB(b,c)&&AwinB(c,a))||(AwinB(a,c)&&AwinB(c,b)&&AwinB(b,a))) //A 击败 B，B 击败 C，C 击败 A 或 A 击败 C，C 击败 B，B 击败 A
                    	return true;
                }
    return false;
}
int main() {
	scanf("%d",&T);
    while(T--) {
        for(int i=1;i<=4;i++) scanf("%d",&a[i]);
        for(int i=1;i<=4;i++) scanf("%d",&b[i]);
		puts(check()? "yes":"no"); //输出
    }
	return 1;
}
```

---

## 作者：tZEROちゃん (赞：0)

一个骰子 4 个面，那么考虑枚举每个面，共枚举 $10^4$ 次。

显然根据题意，当 A 骰子击败 B，B 击败 C，C 击败 A 或 B 击败 A，C 击败 B，A 击败 C 时，显然就是有解的。

此部分代码见完整代码的 `ck` 函数。

考虑直接模拟判断，记 $K_1$ 表示 A 赢 B 的次数，$K_2$ 表示 B 赢 A 的次数，当 $a_i > b_j$ 时，$K_1 \leftarrow K_1 + 1$，当 $a_i < b_j$ 时，$K_2 \leftarrow K_2 + 1$。完整代码如下

### Code

```cpp
bool kwi(int a[], int b[]) {
  int qwq[3] = {0}; 
  rep (i, 1, 4) rep (j, 1, 4) {
    if (a[i] > b[j]) ++qwq[1];
    if (a[i] < b[j]) ++qwq[0];
  }
  return qwq[1] > qwq[0];
}

bool ck(int a[], int b[]) {
  rep (i, 1, 10) rep (j, 1, 10) rep (k, 1, 10) rep (l, 1, 10) {
    int c[5];
    c[1] = i, c[2] = j, c[3] = k, c[4] = l;
    if (kwi(a, b) && kwi(b, c) && kwi(c, a)) return 1;
    if (kwi(b, a) && kwi(c, b) && kwi(a, c)) return 1;
  }
  return 0;
}

int main(){
  int N; iocin >> N;
  while (N--){
    int a[5], b[5];
    rep (i, 1, 4) iocin >> a[i];
    rep (i, 1, 4) iocin >> b[i];
    printf(ck(a, b) ? "yes\n" : "no\n");
  }
  return 0;
}
```

---

## 作者：happybob (赞：0)

传送门：[P8091 [USACO22JAN] Non-Transitive Dice B](https://www.luogu.com.cn/problem/P8091)

# 题意

多组测试，每次给定两个骰子，需要求出是否有另外一个骰子满足这三个骰子是非传递性，传递性定义请看题意。

# 解法

因为骰子只有 $4$ 个面，所以可以考虑深搜加模拟。暴力搜索每一种情况，每种情况判断一次。总共的方案数有 $10^4$ 种，可以通过本题。

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

#define int long long

const int N = 10;
int a[N][5];

inline bool check()
{
	for (int i = 1; i <= 3; i++)
	{
		int losecnt = 0, wincnt = 0;
		for (int j = 1; j <= 3; j++)
		{
			if (i == j) continue;
			int lc = 0, wc = 0;
			for (int k = 1; k <= 4; k++)
			{
				for (int p = 1; p <= 4; p++)
				{
					if (a[i][k] > a[j][p]) wc++;
					else if (a[i][k] < a[j][p]) lc++;
				}
			}
			if (wc > lc) wincnt++;
			else if (wc < lc) losecnt++;
		}
		if (losecnt > wincnt || losecnt < wincnt) return false;
	}
	return true;
}

inline bool dfs(int depth)
{
	if (depth > 4)
	{
		if (check())
		{
			puts("yes");
			return true;
		}
		return false;
	}
	for (int i = 1; i <= 10; i++)
	{
		a[3][depth] = i;
		bool f = dfs(depth + 1);
		if (f)
		{
			return true;
		}
	}
	return false;
}

signed main()
{
	int t;
	scanf("%lld", &t);
	while (t--)
	{
		scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &a[1][1], &a[1][2], &a[1][3], &a[1][4], &a[2][1], &a[2][2], &a[2][3], &a[2][4]);
		if (!dfs(1))
		{
			puts("no");
		}
	}
	return 0;
}
```


---

## 作者：yukimianyan (赞：0)

暴力枚举。

「我们称骰子 X 击败骰子 Y，如果骰子 X 比骰子 Y **更有可能**赢得这局游戏」，这是本题题意重点，它的意思是：

>骰子 X 和骰子 Y 分别投掷，一共有 $4^2=16$ 种情况。这 $16$ 种情况，可分成三类：
>1. 骰子 X 投掷的点数大于骰子 Y 投掷的点数，也就是骰子 X 获胜；
>2. 骰子 X 投掷的点数等于骰子 Y 投掷的点数，也就是骰子 X 和骰子 Y 平局；
>3. 骰子 X 投掷的点数小于骰子 Y 投掷的点数，也就是骰子 Y 获胜；
>
>则，「骰子 X 击败骰子 Y」，意味着 $16$ 种情况中，骰子 X 获胜的数量大于骰子 Y 获胜的数量。

我们可以判断骰子 X 是否击败骰子 Y 了，$O(n^2)$ 或者排序后跑两遍双指针（具体见代码）。

注意到骰子所有可能性只有 $10^4$ 种，我们可以枚举 $c$，判断 $a,b,c$ 是否符合题目要求，显然不会超时。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n=4;
struct ccf{
	int a[10];
	int& operator[](int i){return a[i];}
	void srot(){sort(a+1,a+n+1);}
	friend int operator/(ccf a,ccf b){//a/b 为骰子 a 获胜的情况数
		int res=0;
        //a,b 已经排序
		for(int i=1,j=0;i<=n;i++){
			while(j+1<=n&&b[j+1]<a[i]) j++;
			res+=j;//a[i] 能击败 b[1...j]，累加
            //由于 a[i] 单调不降，j 也单调不降，因此双指针正确
		}
		return res;
	}
	friend bool operator>(ccf a,ccf b){
		return a/b>b/a;
        //骰子 a 获胜的情况数 > 骰子 b 获胜的情况数 即为骰子 a 击败骰子 b
	}
};
int cnt=0;
ccf a,b,ok[10010];
void dfs(int now){//预处理所有排序后骰子
	if(now>n) return ok[++cnt]=a,void();
	for(int i=1;i<=10;i++) a[now]=i,dfs(now+1); 
}
int mian(){
	a.srot(),b.srot();
	for(int i=1;i<=cnt;i++){
		if(a>b&&b>ok[i]&&ok[i]>a) return puts("yes"),0;
	}
	swap(a,b);
	for(int i=1;i<=cnt;i++){
		if(a>b&&b>ok[i]&&ok[i]>a) return puts("yes"),0;
	}
	puts("no");
	return 0;
}
void reset(){
	
}
int main(){
	dfs(1);
	for(scanf("%*d");~scanf("%d%d%d%d%d%d%d%d",&a[1],&a[2],&a[3],&a[4],&b[1],&b[2],&b[3],&b[4]);reset(),mian());
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
给定两个四面骰子 $A,B$ 每个面的点数 $A_1,A_2,A_3,A_4,B_1,B_2,B_3,B_4$，求是否能够构造出一个四面骰子 $C$，使得 $A,B,C$ 三个骰子之间不存在两个骰子获胜的概率相同，也不存在一个骰子能够同时比另外两个骰子有更高概率获胜。

**数据范围：$T$ 组数据，$1\leqslant T,A_i,B_i\leqslant 10$。**

## Solution
由于数据范围很小，因此我们可以直接枚举所有可能的骰子 $C$ 的四个面的点数，然后一个一个去判断是否满足题面中的条件即可。

## Code
```cpp
namespace Solution {
	int a[7], b[7], c[7];
	
	ib chk(int *a1, int *a2, int *a3) {
		int cnt1 = 0, cnt2 = 0;
		F(int, i, 1, 4) F(int, j, 1, 4) cnt1 += (a1[i] > a2[j]), cnt2 += (a1[i] < a2[j]);
		if(cnt1 <= cnt2) return 0;
		cnt1 = cnt2 = 0;
		F(int, i, 1, 4) F(int, j, 1, 4) cnt1 += (a2[i] > a3[j]), cnt2 += (a2[i] < a3[j]);
		if(cnt1 <= cnt2) return 0;
		cnt1 = cnt2 = 0;
		F(int, i, 1, 4) F(int, j, 1, 4) cnt1 += (a3[i] > a1[j]), cnt2 += (a3[i] < a1[j]);
		return cnt1 > cnt2;
	}
	
	iv Main() {
		MT {
			F(int, i, 1, 4) read(a[i]);
			F(int, i, 1, 4) read(b[i]);
			int fl = 0;
			for(c[1] = 1; c[1] <= 10; ++c[1]) {
				for(c[2] = 1; c[2] <= 10; ++c[2]) {
					for(c[3] = 1; c[3] <= 10; ++c[3]) {
						for(c[4] = 1; c[4] <= 10; ++c[4]) {
							if(chk(a, b, c) || chk(a, c, b) || chk(b, a, c) || chk(b, c, a) || chk(c, a, b) || chk(c, b, a)) {yes, fl = 1; break;}
						}
						if(fl) break;
					}
					if(fl) break;
				}
				if(fl) break;
			}
			if(!fl) no;
		}
		return;
	}
}
```

---

## 作者：Onana_in_XMFLS (赞：0)

数据范围极小，故考虑直接**暴力**

符合条件的情况无疑就两种——

$A>B$ 且 $B>C$ 且 $C>A$ 

或者是 $B>A$ 且 $C>B$ 且 $A>C$ 

于是就可以首先预处理出 $A$ 和 $B$ 的关系，代码如下

```cpp
for(int i = 0;i < 4;++i) cin>>a[i];
        for(int i = 0;i < 4;++i) cin>>b[i];
        int a1 = 0,b1 = 0;
        for(int i = 0;i < 4;++i)
            for(int j = 0;j < 4;++j)
            {
                if(a[i] > b[j]) ++a1;
                if(a[i] < b[j]) ++b1;
            }
```

这样比较 $a1$ 和 $b1$ 的大小关系，便可以得到 $A$ 和 $B$ 的大小关系了.

之后便可以直接四层循环暴力枚举骰（tou）子 $C$ 的四个数，之后再判断是否符合上述两种情况之一即可。

考场代码如下（~~奇丑无比~~）

```cpp
#include <bits/stdc++.h>
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
#define mem(arr,val) memset((arr),(val),(sizeof(arr)))
#define INT vector<int>
using namespace std;
const int INF = 0x3f3f3f;
int T,a[4],b[4];
inline bool check(int a,int b,int c,int a2,int b2,int c2)//判断情况是否合法
{
    if(a > b && c > a2 && b2 > c2) return true; 	//A＞B&&C＞A&&B＞C
    if(b > a && c2 > b2 && a2 > c) return true;		//B＞A&&C＞B&&A＞C
    return false;
}
int main(int argc,char *argv[])
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL),cout.tie(NULL);
	cin>>T;
    while(T--)
    {
        bool flag = false;
        for(int i = 0;i < 4;++i) cin>>a[i];
        for(int i = 0;i < 4;++i) cin>>b[i];
        int a1 = 0,b1 = 0;
        for(int i = 0;i < 4;++i)
            for(int j = 0;j < 4;++j)
            {
                if(a[i] > b[j]) ++a1;
                if(a[i] < b[j]) ++b1;
            }
        //cout<<a1<<" "<<b1<<endl;
        for(int i = 1;i <= 10;++i)
        {
            for(int j = 1;j <= 10;++j)
            {
                for(int k = 1;k <= 10;++k)
                {
                    for(int w = 1;w <= 10;++w)//四层循环暴力枚举骰子C的四个数
                    {
                        int a2 = 0,c = 0,b2 = 0,c2 = 0;
                        for(int x = 0;x < 4;++x)
                        {
                        	//得到A和C的胜负关系
                            if(a[x] > i) ++a2;
                            if(a[x] < i) ++c;
                            if(a[x] > j) ++a2;
                            if(a[x] < j) ++c;
                            if(a[x] > k) ++a2;
                            if(a[x] < k) ++c;
                            if(a[x] > w) ++a2;
                            if(a[x] < w) ++c;
                        }
                        for(int x = 0;x < 4;++x)
                        {
                        	//得到B和C的胜负关系
                            if(b[x] > i) ++b2;
                            if(b[x] < i) ++c2;
                            if(b[x] > j) ++b2;
                            if(b[x] < j) ++c2;
                            if(b[x] > k) ++b2;
                            if(b[x] < k) ++c2;
                            if(b[x] > w) ++b2;
                            if(b[x] < w) ++c2;
                        }
                        if(check(a1,b1,c,a2,b2,c2)) {puts("yes");flag = true;break;}//合法就输出"yes"并break掉循环
                    }
                    if(flag) break;
                }
                if(flag) break;     
            }
            if(flag) break;
        }           
        if(!flag) puts("no");//循环完没有合法方案便是"no"
    }
    return 0;
}

```

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题思路是暴力枚举，只需暴力遍历骰子 $C$ 的四个数字从 $1$ 到 $10$，并依次判断 $A,B,C$ 的胜负情况，判断是否可行即可。

只需写两个函数：

1. 用来检验两个骰子谁胜利概率大。方法为：两层循环暴力遍历两个骰子的 $4 \times 4=16$ 中情况，统计胜负次数进行比较

1. 用来验证三个骰子是否符合条件，需要调用上一个函数进行两两胜负判断

## AC CODE：

```cpp
/*
ID:yinhy09
LANG:C++
TASK:Non-Transitive Dice
*/
#include<bits/stdc++.h>
using namespace std;
struct s//用结构体实现骰子
{
	int v[10];
};
s aa,bb,cc;
int check2(s a,s b)//函数1
{
	int ab_a=0,ab_b=0;
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
		{
			if(a.v[i]>b.v[j])ab_a++;
			else if(a.v[i]<b.v[j])ab_b++;
		}
	}
	if(ab_a>ab_b)return 1;
	if(ab_a==ab_b) return 0;
	return -1;
}
bool check3(s a,s b,s c)//函数2
{
	if(check2(a,b)==0||check2(a,c)==0||check2(b,c)==0)return false;
	if(check2(a,b)==1&&check2(a,c)==1)return false;
	if(check2(b,a)==1&&check2(b,c)==1)return false;
	if(check2(c,a)==1&&check2(c,b)==1)return false;
	return true;
}
int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		bool flag=0;
		for(int i=1;i<=4;i++) cin>>aa.v[i];
		for(int i=1;i<=4;i++) cin>>bb.v[i];
		for(int p=1;p<=10&&flag==0;p++)//暴力
		{
			for(int q=1;q<=10&&flag==0;q++)
			{
				for(int r=1;r<=10&&flag==0;r++)
				{
					for(int s=1;s<=10&&flag==0;s++)
					{
						cc.v[1]=p,cc.v[2]=q,cc.v[3]=r,cc.v[4]=s;
						if(check3(aa,bb,cc)==1)//判断
						{
							cout<<"yes"<<endl;
							flag=1;
						}
					}
				}
			}
		}
		if(flag==1)continue;
		cout<<"no"<<endl;
	}
	return 0;
}
```

谢谢观看~

---

## 作者：CANTORSORT (赞：0)

众所周知，每一次打开题目，我们都要注意 **数据范围**。

emmm……

$1\le T\le 10$

并且，我们要枚举的这个骰子是一个 **四面骰子**，而每一面上的数字 **仅仅是 $1\sim 10$**。

考虑深搜。

每次从 $1\sim 10$ 里选一个数字，如此执行 $4$ 次，时间复杂度为 $O(10^4\times T)$，**完全可以通过**。

再来分析一下 **判定函数**：

举个栗子，
$A=\{4,5,6,7\}$
$B=\{2,4,5,10\}$

其中，有：
$A_1>B_1,A_2>B_1,A_3>B_1\dots$

合起来，
**序列 $A$ 中的数字大于 $B$ 的有 $9$ 次**；
**序列 $B$ 中的数字大于 $A$ 的则有 $5$ 次**！

因此，我们就说 **$A$ 能战胜 $B$**！

由此，可得出以下程序：
```cpp
bool check(int x[],int y[]) //计算x能否赢y
{
	int cntx=0,cnty=0;
	for(int i=1;i<5;i++)
	{
		for(int j=1;j<5;j++)
		{
			if(x[i]>y[j])
				++cntx;
			else if(x[i]<y[j])
				++cnty;
		}
	}
	return cntx>cnty;
}
```
至此，这一题完全结束。
下面给出 **完整代码**。
## Code:
```cpp
#include<bits/stdc++.h>
#define isdight(c) (c>='0'&&c<='9')
using namespace std;
int t,a[5],b[5],c[5],flag=0;
inline int read() //快读
{
	int x=0,f=1;
	char c=getchar();
	while(!isdight(c))
		f=(c^'-'?1:-1),c=getchar();
	while(isdight(c))
		x=(x<<1)+(x<<3)+(c-'0'),c=getchar();
	return x*f;
}
bool check(int x[],int y[]) //计算x能否赢y
{
	int cntx=0,cnty=0;
	for(int i=1;i<5;i++)
	{
		for(int j=1;j<5;j++)
		{
			if(x[i]>y[j])
				++cntx;
			else if(x[i]<y[j])
				++cnty;
		}
	}
	return cntx>cnty;
}
void dfs(int dep) //核心部分
{
	if(dep>4)
	{
		if((check(a,b)&&check(b,c)&&check(c,a))||(check(b,a)&&check(a,c)&&check(c,b))) //满足非传递性
			flag=1;
		return;
	}
	if(flag)
		return;
	for(int i=1;i<11;i++) //递归
	{
		c[dep]=i;
		dfs(dep+1);
	}
}
int main()
{
	t=read();
	while(t--)
	{
		flag=0;
		for(int i=1;i<5;i++)
			a[i]=read();
		for(int i=1;i<5;i++)
			b[i]=read();
		sort(a+1,a+5);
		sort(b+1,b+5);
		//排序，预处理
		dfs(1);
		if(flag)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
```

---

