# [GCJ 2020 Qualification] Parenting Partnering Returns

## 题目描述

Cameron 和 Jamie 的孩子快 3 岁了！虽然孩子现在更独立了，但安排孩子的活动和家务对这对夫妇来说仍然是个挑战。

Cameron 和 Jamie 需要共同完成 $\mathbf{N}$ 项当天的活动。每项活动都在一天中的特定时间段进行。他们需要将这些活动分配给两人，确保每人不会被分配到时间重叠的两项活动。注意：一项在时间 $\mathbf{t}$ 结束的活动与另一项在时间 $\mathbf{t}$ 开始的活动不算重叠。

例如，假设 Jamie 和 Cameron 需要安排 3 项活动：第一项从 18:00 到 20:00，第二项从 19:00 到 21:00，第三项从 22:00 到 23:00。一种可能的分配方式是 Jamie 负责第二项活动（19:00-21:00），Cameron 负责另外两项。另一种有效分配是 Cameron 负责第一项活动（18:00-20:00），Jamie 负责另外两项。注意前两项活动在 19:00 至 20:00 期间重叠，因此不能将它们分配给同一个人。

给定每项活动的开始和结束时间，找出任意一个不要求同一人承担重叠活动的排班方案，或者判定这是不可能的。


## 说明/提示

**样例解释**

样例 #1 对应题目描述中的情况。如所述，还存在其他有效解，例如 `JCJ` 和 `JCC`。

样例 #2 中，三项活动互相重叠。无论如何分配都会导致至少一人承担两项重叠活动，因此无解。

样例 #3 中，注意 Cameron 在 100 分钟时结束一项活动并立即开始另一项活动。

样例 #4 中，任意分配方案都有效。特别地，允许一人承担所有活动。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$；
- $0 \leq \mathbf{S}_{\mathbf{i}} < \mathbf{E}_{\mathbf{i}} \leq 24 \times 60$。

**测试集 1（7 分，可见判定）**

- $2 \leq \mathbf{N} \leq 10$。

**测试集 2（12 分，可见判定）**

- $2 \leq \mathbf{N} \leq 1000$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3
360 480
420 540
600 660
3
0 1440
1 3
2 4
5
99 150
1 100
100 301
2 5
150 250
2
0 720
720 1440```

### 输出

```
Case #1: CJC
Case #2: IMPOSSIBLE
Case #3: JCCJJ
Case #4: CC```

# 题解

## 作者：LiHen_Yan (赞：2)

## P13050 [GCJ 2020 Qualification] Parenting Partnering Returns 题解

### Problem

给定 $n$ 个区间，将这 $n$ 个区间分为两组，使得每组中所有区间没有交集。

### Solution
经典贪心问题，类似于那个选最少区间的问题，先把所有区间按照左端点排序，枚举每个区间，再记录一下当前这两组所选的区间中最右面的点，如果当前这个区间的右端点在其中一个的右面，那么这个区间就可以分到这组，如果第一组不行再考虑第二组，如果当前区间右端点在第二组最右面的点右面，那就可以分给第二组，如果都不能分就是无解的情况。

把左右端点和区间编号存到结构体里排序，然后注意排完序后第 $i$ 个任务对应的原任务就是 $id_i$，存一下答案最后输出即可。

### Code

```cpp
#include <bits/stdc++.h>
constexpr int maxn = 1010;
struct node{
	int l, r, id;
}a[maxn];
int n, T;
inline bool cmp(node a, node b){
	return a.l < b.l;
}
inline void solve(int ca){
	std::cin >> n;
	for(int i = 1; i <= n; i++){
		std::cin >> a[i].l >> a[i].r;
		a[i].id = i;
	}
	std::sort(a + 1, a + n + 1, cmp);
	int end1 = -2e9, end2 = -2e9;
	std::string ans(n, 'A');
	
	for(int i = 1; i <= n; i++){
		if(a[i].l >= end1){
			end1 = a[i].r;
			ans[a[i].id - 1] = 'C';
		}
		else if(a[i].l >= end2){
			end2 = a[i].r;
			ans[a[i].id - 1] = 'J';
		}
		else{
			std::cout << "Case #" << ca << ": IMPOSSIBLE" << '\n';
			return;
		}
	}
	std::cout << "Case #" << ca << ": " << ans << '\n';
	
}
int main(){
	std::cin >> T;
	for(int ca = 1; ca <= T; ca++){
		solve(ca);
	}
}
```

---

## 作者：Doraeman (赞：1)

~~不用看算法标签就知道~~，这题就是一道普通贪心。~~建议降橙。~~
## 思路
### 大致思路
贪心题，首先排序。按照活动开始时间排序，可以帮助我们记录二人的做活动结束时间，并根据时间分配活动。
设 Cameron 和 Jamie 每次做完当前活动后，时间分别为 $E_c,E_j$。
### 拆分详解
#### Cameron
第 $i$ 个活动的开始时间 $S_i$，如果满足 $E_c\leq S_i$，也就说明第 $i$ 项活动开始时（$S_i$ 时刻），Cameron 已经做完了当前所有的活动，**也就是说 Cameron 现在是闲着的**！他可以**立刻去做第 $i$ 项活动**！此时**将 $E_c$ 更新为第 $i$ 项活动的结束时刻 $E_i$**。
#### Jamie
反之，如果不满足上述 $E_c\leq S_i$ 的条件，说明当时 Cameron 真的很忙！  
同理，此时如果满足 $E_j\leq S_i$，**那么 Jamie 就应该去做第 $i$ 项活动了**。**并将 $E_j$ 更新为第 $i$ 项活动的结束时刻 $E_i$**。
#### IMPOSSIBLE
最后，如果上述两个条件都不满足，那么实在是没有人来做这项活动了！输出 ```IMPOSSIBLE```。
#### 补充说明
这道题很显然有多解，为了避免纠结，我们可以每次遇到活动时，只要 Cameron 有时间就让他干；他没时间再让 Jamie 干。  
尽管如此，**上述思路中 Cameron 和 Jamie 是可以互换的**。而且有时两个人都可以做。
## 细节
### 字符串记录答案
如果我们在活动记录表（排序后）的循环中直接输出 C 或 J，那么可能最后发现分配无解，而这些输出就变成多余的内容。  
所以循环过程中可以用一个数组来保存答案，并在最后确认分配有解之后再输出所有答案。
### 记录活动编号
这道题在记录 $S$ 和 $E$（活动的开始结束时间）时最好使用 Struct 结构，因为我们还需要记录活动编号。

排序后活动顺序与输入顺序不符。**但是题目要求我们按照输入顺序输出答案，所以我们不得不保存编号，记录答案时也按照输入顺序记录（很重要！）。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+5;

int n;
struct Act{ // 活动 struct保存 
    int s, e, id;
}a[N];
bool cmp(Act x, Act y){ // 按照开始时间排序  
    return x.s < y.s;
}

int main(){
    int T; cin >> T;
    for(int _=1; _<=T; _++){
        cin >> n;
        for(int i=1; i<=n; i++){
            cin >> a[i].s >> a[i].e;
            a[i].id = i;
        }
        // 排序  
        sort(a + 1, a + n + 1, cmp);
		
        printf("Case #%d: ",_);
        // Ce,Je是二人当前活动的结束时间  
        int Ce = 0, Je = 0;
        // flag用来记录是否有解；ans记录答案  
        bool flag = 1; int ans[N] = {0};
        for(int i=1; i<=n; i++){
        	// 先判断 C 有没有时间  
            if(a[i].s >= Ce){
            	// 按照输入顺序记录  
                ans[a[i].id] = 'C';
                Ce = a[i].e;
            }
            // 再判断 J  
            else if(a[i].s >= Je){
                ans[a[i].id] = 'J';
                Je = a[i].e;
            }
            // 最后二人都没有时间，无解  
            else{
                flag = 0;
                cout << "IMPOSSIBLE\n";
                break;
            }
        }
        // 如果有解，输出答案  
        if(flag){
        	for(int i=1; i<=n; i++)
        		printf("%c",ans[i]);
        	cout << '\n';
        }
    }
}
```

---

## 作者：All_Wrong_Answer (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13050)

## 思路：

简单贪心题。

看见时间范围只有 $24 \times 60 =1440$，所以考虑用一个类似前缀和的东西记录某个时间点被几个任务覆盖，用桶记一下每个时间点是哪几个区间的开始和结束就可以 $O(n)$ 做出。

当出现任何一个点的值大于等于 $3$ 时，显然无解，因为只有两个人。

然后是贪心过程，先把区间按左端点从小到大排序，左端点相同的按右端点从小到大排序，对于每一个区间都可以暴力跑一遍，有两种情况：
1. 如果这个区间不与任何区间重合就将任务分配给当前完成已分配任务结束时间点靠前的那个人。
2. 与某一区间重合时，如果和它重合的区间在排序后在它后面，按情况一操作即可，否则显然前面的重合区间已经安排了一个人了，把另一个空闲的人安排上去即可。
   
最后输出就行，记得多测清空。

考虑一下复杂度，看起来每个区间都要跑一边是 $O(Tn^2)$ 的，但实际上每个时间点最多只有两个区间同时覆盖，因为被超过两个区间覆盖的点已经被我们判为无解了，那么每组复杂度中的 $n^2$ 就变成了 $2n$，总复杂度 $O(Tn)$，可以通过此题。

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int x;
struct node{
	int l,r,bh;
}m[1005];
bool cmp(node q,node p){
	if(q.l==p.l) return q.r<p.r;
	else return q.l<p.l;
}
int s1[2005],s2[2005];
int qz[2005];
char ans[2005];
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>x;
		for(int j=0;j<=2000;j++) s1[j]=s2[j]=0;
		for(int j=1;j<=x;j++){
			cin>>m[j].l>>m[j].r; 
			s1[m[j].l]++;
			s2[m[j].r]++;
			m[j].bh=j;
		} 
		qz[0]=0;
		int maxa=0;
		for(int j=0;j<=1450;j++){
			if(j!=0) qz[j]=qz[j-1];
			qz[j]+=s1[j];
			qz[j]-=s2[j];
			maxa=max(maxa,qz[j]);
		}
		
		if(maxa>=3){
			cout<<"Case #"<<i<<": IMPOSSIBLE\n";
			continue;
		}
		sort(m+1,m+1+x,cmp);
		int f1=0,f2=0;
		for(int j=1;j<=x;j++){
			int ks=0;
			for(int k=m[j].l;k<=m[j].r;k++) ks=max(ks,qz[k]);
			if(ks==1){
				if(f1<=f2){
					ans[m[j].bh]='J';
					f1=m[j].r;
				} 
				else{
					ans[m[j].bh]='C';
					f2=m[j].r;
				} 	
			}
			else{
				if(f1>m[j].r){
					ans[m[j].bh]='C';
					f2=m[j].r;
				}
				else if(f2>m[j].r){
					ans[m[j].bh]='J';
					f1=m[j].r;
				}
				else{
					if(f1<=f2){
					    ans[m[j].bh]='J';
					    f1=m[j].r;
				    } 
				    else{
				    	ans[m[j].bh]='C';
				    	f2=m[j].r;
				    } 
				}
			}
		}
		cout<<"Case #"<<i<<": ";
		for(int j=1;j<=x;j++) cout<<ans[j];
		cout<<endl;
	}
	return 0; 
}

```

---

## 作者：封禁用户 (赞：0)

# [P13050 [GCJ 2020 Qualification] Parenting Partnering Returns](https://www.luogu.com.cn/problem/P13050)
## 题目描述：
让两个人安排活动，做一件事时不可以最其他事，如果有事情做不了，就输出 `IMPOSSSBLE`，否则输出一行 `Case #x: y`，其中 $\mathbf{x}$ 是测试用例编号（从 1 开始），$\mathbf{y}$ 表示输出一个长度为 $\mathbf{N}$ 的字符串。字符串的第 $\mathbf{i}$ 个字符如果是 $\mathbf{c}$ 表示第 $\mathbf{i}$ 项活动分配给 Cameron，$\mathbf{j}$ 表示分配给 Jamie。

若存在多个解，输出任意一个即可。

## 分析做法：
因为时间给的很足，所以可以随便咋做。

建议用贪心做，先用一个结构体来储存开始时间，结束时间，原始索引（因为排序后会打乱）。再用一个比较函数比较初始时间以用来排序。

接着是主程序：
1. 先输入，再排序。

2. 初始化变量，有四个，分别是存储结果，两人的最后活动结束时间和是否可行（布尔类型）。

3. 贪心操作，先遍历排序后的活动，再判断如果活动可以分配给 Cameron 去做，也就是不与 Cameron 的前一个活动重叠，便标记为 $\mathbf{c}$，更新结束时间，否则尝试分配给 Jamie去做，最后如果都不行，便标记为不可能并终止。

4. 输出结果。

奉上代码，无注释：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
struct f {
    int start;
    int end;
    int index;
};
bool cmp(const f &a, const f &b) {
    return a.start < b.start;
}
signed main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        int n;
        cin >> n;
        f a[1000];
        for (int i = 0; i < n; ++i) {
            cin >> a[i].start >> a[i].end;
            a[i].index = i;
        }
        sort(a, a + n, cmp);
        char res[1000]; 
        int c_end = -1;
        int j_end = -1;
        bool possible = true;

        for (int i = 0; i < n; ++i) {
            if (a[i].start >= c_end) {
                res[a[i].index] = 'C';
                c_end = a[i].end;
            } else if (a[i].start >= j_end) {
                res[a[i].index] = 'J';
                j_end = a[i].end;
            } else {
                possible = false;
                break;
            }
        }
        cout << "Case #" << i << ": ";
        if (possible) {
            for (int i = 0; i < n; ++i) {
                cout << res[i];
            }
            cout << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}
```

谢谢观看，求过求赞。

---

## 作者：4041nofoundGeoge (赞：0)

~~这个题目在某个农夫 John 的农场里也出现过相似的情况。[多倍经验](https://www.luogu.com.cn/problem/P2255)。~~

## 思路

考虑贪心。

记录两个人接下的任务的终点，每一次查询哪些区间可以让每人手上只有一个任务。若两人都没任务，输出 `IMPOSSIBLE`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct p{
  int start,end,id;  
}a[1005];
bool cmp(p a,p b){
    return a.start<b.start;
}
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        memset(a,0,sizeof(a));
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i].start>>a[i].end;
            a[i].id=i;
        }
        sort(a+1,a+n+1,cmp);
        int came,jam;
        came=jam=-1;
        string s = string(n+2, ' ');
        int flag=0;
        cout<<"Case #"<<q-t<<": ";
        for(int i=1;i<=n;i++){
            if(a[i].start>=came){
                s[a[i].id]='C';
                came=a[i].end;
            }
            else if(a[i].start>=jam){
                s[a[i].id]='J';
                jam=a[i].end;
            }
            else{
                puts("IMPOSSIBLE");
                flag=1;
                break;
            }
        }
        if(!flag){
            for(int i=1;i<s.size();i++)cout<<s[i];
            cout<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：jms23012 (赞：0)

## 题意简述

给出若干个时间段的起始点和终点，需要把这些时间段分成两部分，每一部分中的时间段都不与此部分中的另一个时间段重叠。

## 题目分析

因为题目的时间限制十分宽泛，所以考虑时间复杂度是没有必要的，我们可以随意发挥。

一个简单的思路是，先枚举所有的时间段，找出所有互不重叠的时间段，然后看剩余的时间段是否互不重叠。这样就可以筛去三个及以上时间段互相重叠的非法情况。

## 细节处理

如果你用两个数组存储开始时间和结束时间，你就会很愉快地写完代码，很愉快地测过了前两个样例。

咦，第三个样例为什么输出无解？

这时你才发现，**起始时间并不是从小到大输入的**。

这回你学聪明了，把两个数组绑到了一起，然后排了个序。

你很愉快地写完代码，很愉快地测过了前两个样例。

这时你突然发现，你的安排针对的是排完序后的方案顺序，**安排完之后还要把顺序排回来**。

所以这道题的时间段必须用**结构体**存储。

还有一点，某个时间段的结束时间和另一个时间段的起始时间**重合**时，**不算做重叠**。

详情见样例三，不知道测试数据有没有这样的点，这里给一组。

```cpp
sample input:

1
3
1 5
5 10
2 6

sample output:

Case #1: JJC

wrong answer:

Case #1: IMPOSSIBLE
```

## 代码实现

处理好细节后代码就好写了，如下。


```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{ //用结构体存储时间段。
	int beg,en,num;
}a[10005];
bool cmp(node x,node y){ //给结构体排序。
	return x.beg<y.beg;
}
bool cmp1(pair<int,int> x,pair<int,int> y){ //把顺序排回来。
	return x.first<y.first;
}
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int n;
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>a[j].beg>>a[j].en;
			a[j].num=j;
		}
		sort(a+1,a+n+1,cmp); //将时间段按照开始时间从小到大排序，详情可见第三组样例。
		cout<<"Case #"<<i<<": ";
		int fenpei[1500]={},lastend=0;
		for(int j=1;j<=n;j++){
			if(a[j].beg>=lastend){
				fenpei[j]=1;
				lastend=a[j].en;
			}
		}
		int lastend1=0,c=0;
		for(int j=1;j<=n;j++){
			if(fenpei[j]==0){
				
				if(a[j].beg>=lastend1){
					
					lastend1=a[j].en;
				}
				else{ //有三个时间段重叠。
					c=1;
					break;
				}
			}
		}
		if(c==1) cout<<"IMPOSSIBLE";
		else{
			pair<int,int> pa[1500]; //把顺序排回来再输出方案。
			for(int j=1;j<=n;j++){
				pa[j].first=a[j].num;
				pa[j].second=fenpei[j];
			}
			sort(pa+1,pa+n+1,cmp1);
			for(int j=1;j<=n;j++){
				if(pa[j].second==1) cout<<'J';
				else cout<<'C';
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13050)

# 题目分析

首先将问题抽象一下，可以变成这样：给定 $n$ 条线段，能不能将这 $n$ 条线段分成两组，满足任意一组中没有重叠的线段。

对于线段重叠的问题，首先要做的通常是对线段按左端点从小到大排序。

将线段放到数轴上，我们注意到，如果数轴上任意一个点都最多被两条线段所覆盖，则一定可以完成分组，否则一定不能。给一个简要的证明：

设三条线段 $a$，$b$，$c$，$a \cap b$ 表示两个线段相交的部分。若 $a$ 与 $b$ 重叠，则 $a \cap b$ 的部分被两条线段覆盖。若任意一个点都最多被两条线段所覆盖，则 $c \cap (a \cap b)$ 一定为空。此时 $c$ 一定和 $a$，$b$ 中的一个不重叠，则一个人取 $c$ 和与它不重叠的两条线段，另一个人取另外一个。线段数多于 $3$ 的情况以此类推。

相反，若存在一个点被多于 $2$ 个线段所覆盖，则必然存在三条线段 $a$，$b$，$c$，使得它们两两重叠。由于三条线段分给两个人，必然有一个人拿到至少两条，所以这个人拿到的两条必然重叠，因此无解。

现在方向有了，如何实现？一条线段的起点意味着后面会多一条线段，一条线段的终点意味着后面会少一条线段。由于 $0 \le S_i \le E_i \le 24 \times 60$，因此完全可以一个一个点的扫，对于每个点，设 $T_i$ 为第 $i$ 个点覆盖的线段数，$X_i$ 为该点作为线段起点的次数，$Y_i$ 为该点作为终点的次数。则该点的下一个点覆盖的线段数为 $T_i+X_i-Y_i$，即多了 $X_i$ 条，少了 $Y_i$ 条。若发现某点处 $T_i>2$，则无解。

下面考虑如何分配。由于线段已经按左端点从小到大排序，且已经判断有解。因此对与第 $i$ 个线段，只需判断它与第 $i-1$ 条线段是否重叠，如果不重叠则继续分配给分到第 $i-1$ 条线段的人，否则分给另一个人。第一条线段可分给任意一个人。

# 代码


```cpp
#include<bits/stdc++.h>
#define N 2001
using namespace std;
struct str{
	int x,y,id;
}s[N];
int cmp(str a,str b){
	if(a.x!=b.x){
		return a.x<b.x;
	}
	return a.y<b.y;
}
int mem2[N][2]={0};
int main(){
	int t;
	cin>>t;
	char ans[N];
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
		int n,maxx=-1,jl=0,yes=1;
		cin>>n;
		for(int i=0;i<=24*60;i++){
			mem2[i][0]=mem2[i][1]=0;
		}
		for(int i=1;i<=n;i++){
			cin>>s[i].x>>s[i].y;
            s[i].id=i;
			maxx=max(maxx,s[i].y);
			mem2[s[i].x][0]++;
			mem2[s[i].y][1]++;
		}
		for(int i=0;i<=24*60;i++){
			jl+=mem2[i][0]-mem2[i][1];
			if(jl>2){
				cout<<"IMPOSSIBLE"<<endl;
				yes=0;
				break;
			}
		}
		if(!yes){
			continue;
		}
		sort(s+1,s+1+n,cmp);
		ans[s[1].id]='C';
		char now='C';
		for(int i=2;i<=n;i++){
			if(s[i].x>=s[i-1].y){
				ans[s[i].id]=now;
			}
			else{
				if(now=='C'){
					now='J';
				}
				else{
					now='C';
				}
				ans[s[i].id]=now;
			}
		}
		for(int i=1;i<=n;i++){
			cout<<ans[i];
		}
		cout<<endl;
	}
	return 0;
}
```

---

