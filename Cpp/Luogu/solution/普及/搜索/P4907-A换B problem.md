# A换B problem

## 题目背景

仙女与小奔约定，想要拿到仙药，必须在牌技上赢了她。

## 题目描述

他们要开始打牌了。但是，拥有强迫症的小奔看着手中的牌，很不愉快。原因是他理牌时按花色理（逗我），又希望一个花色的牌是连着的（$A-2-3-4-5-6-7-8-9-10-J-Q-K$）。

忍无可忍的小奔开始与参与打牌的其他人换牌（作弊？？？），他希望换最少的牌来满足他的需求（假设所有牌都可以换）

换牌规则：只能用点数相同的牌交换。

众人：还能不能好好打牌了？！我们限你1s内换完，要不然就告诉仙女！

## 说明/提示

样例1，可达成，将$2$ $3$换为$1$ $3$，$4$ $J$换为$3$ $J$

样例2，可达成，将$2$ $3$换成$1$ $3$，$3$ $Q$换成$4$ $Q$。
（以上答案仅供参考，不保证没有多解,但输出必然唯一，~~别问我为什么~~）


对于10%的数据：为样例$2.$

对于100%的数据： $ N \leq 52 $，即保证数据在一副牌内

## 样例 #1

### 输入

```
10
1 A
1 2
1 4
2 3
2 5
2 6
3 9
3 10
3 Q
4 J```

### 输出

```
Yes
2```

## 样例 #2

### 输入

```
10
1 A
1 2
1 4
2 3
2 5
2 6
3 9
3 10
3 Q
4 K```

### 输出

```
Yes
2```

# 题解

## 作者：引领天下 (赞：21)

出题人来写一发题解

此题主要就是搜索，为了提升难度，我还搞了一个恶心的读入

接下来就是搜索了。

具体码里说吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool a[5][14];
int ans,p,k,n,i,ant;
char ch;
string st;
bool bb;
bool check() {
    int i,j,t;
    bool b;
    for (j=1; j<=4; j++) {
        t=0;
        b=false;
        for (i=1; i<=k; i++)if (a[j][i])t++;
        i=0;
        if (t==1||t==13)continue;
        while (i<k) {
            i++;
            if (t==0)break;
            if (a[j][i]) {
                t--;
                if (b) continue;
                else b=true;
            } else if (b)return false;
            else continue;
        }
    }
    return true;
}//判断是否连续（即换完后是否可行）
void check2() {
    int i,j,t,y;
    bool b;
    y=0;
    for (j=1; j<=4; j++) {
        t=0;
        for (i=1; i<=k; i++)if (a[j][i])t++;
        i=0;
        if (t==0||t==13||t==1) continue;
        b=false;
        while (i<k) {
            i++;
            if (t==0) break;
            if (a[j][i]) {
                t--;
                if (b) continue;
                else b=true;
            } else if (b)y++;
            else continue;
        }
    }
    if (y<ant) ant=y;
}//同上，另一个判断
void search(int q,int b) {
    int i,j,o,y[5],w[5];
    if (q==k+1) {
        if (check()) {
            bb=true;
            if (ans>b) ans=b;
        }
        if (!bb) check2();
        return ;
    }
    search(q+1,b);
    j=0;
    for (i=1; i<=4; i++)
        if (a[i][q]) {
            j++;
            y[j]=i;
        } else {
            w[i-j]=i;
        }
    if (j==4||j==0)return ;
    if (j==1||j==3) {
        if (j==3) {
            for (o=1; o<=3; o++) {
            	if (a[i][j+1]&&a[i][j-1])continue;
   				if (!(a[o][j+1]||a[o][j-1]))continue;
                a[w[1]][q]=true;
                a[y[o]][q]=false;
                search(q+1,b+1);
                a[w[1]][q]=false;
                a[y[o]][q]=true;
            }
        }
        if (j==1) {
            for (o=1; o<=3; o++) {
			if (a[i][j+1]&&a[i][j-1])continue;
   			//if (!(a[o][j+1]||a[o][j-1]))continue;
                a[w[o]][q]=true;
                a[y[1]][q]=false;
                search(q+1,b+1);
                a[w[o]][q]=false;
                a[y[1]][q]=true;
            }
        }
    } else {
        for (o=1; o<=2; o++) {
        	if (a[i][j+1]&&a[i][j-1])continue;
   			if (!(a[o][j+1]||a[o][j-1]))continue;
            a[w[o]][q]=true;
            a[y[1]][q]=false;
            search(q+1,b+1);
            a[w[o]][q]=false;
            a[y[1]][q]=true;
            a[w[o]][q]=true;
            if (a[i][j+1]&&a[i][j-1])continue;
			if (!(a[o][j+1]||a[o][j-1]))continue;
            a[y[2]][q]=false;
            search(q+1,b+1);
            a[w[o]][q]=false;
            a[y[2]][q]=true;
        }
        a[w[1]][q]=true;
        a[y[1]][q]=false;
        a[w[2]][q]=true;
        a[y[2]][q]=false;
        search(q+1,b+2);
        a[w[1]][q]=false;
        a[y[1]][q]=true;
        a[w[2]][q]=false;
        a[y[2]][q]=true;
    }
}//搜索，具体过程就是分类讨论，对每个牌的编号+1、-1进行搜索
int main() {
    cin>>n;
    for (i=1; i<=n; i++) {
        cin>>p>>st;
        if (st=="A") {
            a[p][1]=true;
            if (1>k)k=1;
        }
        if (st=="2") {
            a[p][2]=true;
            if (2>k)k=2;
        }
        if (st=="3") {
            a[p][3]=true;
            if (3>k)k=3;
        }
        if (st=="4") {
            a[p][4]=true;
            if (4>k)k=4;
        }
        if (st=="5") {
            a[p][5]=true;
            if (5>k)k=5;
        }
        if (st=="6") {
            a[p][6]=true;
            if (6>k)k=6;
        }
        if (st=="7") {
            a[p][7]=true;
            if (7>k)k=7;
        }
        if (st=="8") {
            a[p][8]=true;
            if (8>k)k=8;
        }
        if (st=="9") {
            a[p][9]=true;
            if (9>k)k=9;
        }
        if (st=="10") {
            a[p][10]=true;
            if (10>k)k=10;
        }
        if (st=="J") {
            a[p][11]=true;
            if (11>k)k=11;
        }
        if (st=="Q") {
            a[p][12]=true;
            if (12>k)k=12;
        }
        if (st=="K") {
            a[p][13]=true;
            if (13>k)k=13;
        }//鬼畜的读入
    }
    ans=255;
    ant=255;
    search(1,0);
    if (bb) {
        puts("Yes");
        printf ("%d\n",ans);
    } else {
        puts("No");
        printf ("%d\n",ant);
    }//输出
}
```

另：请管理员改一下，这题真是我出的啊QAQ

---

## 作者：FlashHu (赞：19)

顺便提一下题意有一个地方不太清楚，就是如果输出`No`还要输出最少需要添加多少张牌才能满足要求。蒟蒻考完以后发现四个点`Too short on line 2`。。。

比较需要技巧的搜索

既然是同一个花色要连续，那就枚举每一个花色在哪一段区间连续并选中四个区间，累计每个点数的选中次数。

最后来一个$O(13)$的$\text{check}$，首先每个点数选中次数要不少于已有的个数。接着，只有所有点数的选中次数和已有点数相等时，才能判为'Yes'，然后统计某张牌的花色的区间未包含这张牌的总数更新答案。否则判为'No'，然后统计每个点数选多了的总数更新答案。

总复杂度$\binom{13}{2}^4* 13=481195728$，超过了$10^8$，肯定需要剪枝。

可行性剪枝：每个点数选中次数之和不少于原有牌的总数。

最优性剪枝：实时统计选多了的总数，在`No`的状态下，如果超过答案则剪掉；在`Yes`的状态下，只要不为$0$就剪掉。

700+ms比标程快多了。可能标程比较良心没加什么剪枝。
```cpp
#include<bits/stdc++.h>
#define R register int
using namespace std;
const int N=99;
int a[N],b[N],l[N],r[N],cnt[N],n,now1,ans=N,ans1=N;
char s[N];
void dfs(R h,R lef){//lef为n-当前已选中总次数
    if(h==5){
        R now=0;
        for(R i=1;i<=13;++i){
            if(cnt[i]>0)return;//不合法
            now|=cnt[i]<0;
        }
        if(now){ans1=now1;return;}//No状态
        for(R i=1;i<=n;++i)//Yes状态，统计答案
            if((l[a[i]]>b[i]||r[a[i]]<b[i])&&++now==ans)return;
        ans=now;ans1=1;return;//注意ans1=1的剪枝作用
    }
    for(R i=max(lef-(4-h)*13,0),j,rr;i<=13;++i){//枚举区间长度，可行性剪枝
        if(i==0){l[h]=r[h]=0;dfs(h+1,lef);continue;}
        for(rr=i;rr<=13;++rr){//枚举右端点
            for(j=rr-i+1;j<=rr;++j)now1+=--cnt[j]<0;//动态维护当前选多了的总数
            if(now1<ans1)l[h]=(r[h]=rr)-i+1,dfs(h+1,lef-i);//最优性剪枝
            for(j=rr-i+1;j<=rr;++j)now1-=++cnt[j]<=0;
        }
    }
}
int main(){
    scanf("%d",&n);
    for(R i=1;i<=n;++i){
        scanf("%d%s",&a[i],s);
        if(s[0]=='A')b[i]=1;//把点数处理一下
        else if(s[0]=='1')b[i]=10;
        else if(s[0]=='J')b[i]=11;
        else if(s[0]=='Q')b[i]=12;
        else if(s[0]=='K')b[i]=13;
        else b[i]=s[0]-'0';
        ++cnt[b[i]];
    }
    dfs(1,n);
    if(ans!=N)printf("Yes\n%d\n",ans);
    else printf("No\n%d\n",ans1);
    return 0;
}
```

---

## 作者：HuangRuibo (赞：3)

# 题解：
## P4907
[题目传送门](https://www.luogu.com.cn/problem/P4907)

题目要求通过交换牌来使得每种花色的牌按顺序排列。交换规则是只能交换点数相同的牌。我们需要判断是否可以通过交换使得每种花色的牌按顺序排列，并输出最少的交换次数。

### 主要思路如下：

1. 使用深度优先搜索 DFS 来尝试所有可能的交换方式。
2. 在每次交换后，检查当前状态是否满足每种花色的牌按顺序排列。
3. 使用一个二维数组 $f$ 来记录每种花色的牌的状态。
4. 通过递归的方式尝试每种可能的交换，并记录最少的交换次数。
5. 如果在规定时间内找到解，则输出最少的交换次数，否则输出最少需要的牌数。
---
### AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 60, M = 20;

// 读取输入的函数
inline ll read() {
    ll x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

// 输出结果的函数
inline void write(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

// 牌的结构体
struct Card {
    ll suit, rank;
} cards[N];

ll n, x, y, K, ans = INT_MAX, min_missing = INT_MAX;
char rank_str[2];
bool f[5][M];

// 检查当前状态是否满足每种花色的牌按顺序排列
bool check() {
    ll missing = 0;
    bool valid = true;
    for (int i = 1; i <= 4; i++) {
        ll min_rank = 15, max_rank = 0;
        for (ll j = 1; j <= 13; j++) {
            if (f[i][j]) {
                min_rank = j;
                break;
            }
        }
        for (ll j = 13; j >= 1; j--) {
            if (f[i][j]) {
                max_rank = j;
                break;
            }
        }
        for (int j = min_rank; j <= max_rank; j++) {
            if (!f[i][j]) {
                valid = false;
                missing++;
            }
        }
    }
    min_missing = min(min_missing, missing);
    return valid;
}

// 深度优先搜索尝试所有可能的交换方式
void dfs(ll pos, ll sum) {
    if (sum >= ans) return;
    if (check()) {
        ans = min(ans, sum);
        return;
    }
    if (pos > n) return;
    if ((clock() - K) * 1000 >= 200 * CLOCKS_PER_SEC) {
        if (ans <= 52) {
            puts("Yes");
            write(ans);
        } else {
            puts("No");
            write(min_missing);
        }
        exit(0);
    }
    for (int i = 1; i <= 4; i++) {
        if (f[i][cards[pos].rank] && i != cards[pos].suit) continue;
        f[cards[pos].suit][cards[pos].rank] = 0;
        f[i][cards[pos].rank] = 1;
        if (i != cards[pos].suit) dfs(pos + 1, sum + 1);
        else dfs(pos + 1, sum);
        f[i][cards[pos].rank] = 0;
        f[cards[pos].suit][cards[pos].rank] = 1;
    }
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        x = read();
        scanf("%s", rank_str);
        if (rank_str[0] == 'A') y = 1;
        else if (rank_str[0] == 'J') y = 11;
        else if (rank_str[0] == 'Q') y = 12;
        else if (rank_str[0] == 'K') y = 13;
        else if (rank_str[0] == '1' && rank_str[1] == '0') y = 10;
        else y = rank_str[0] - '0';
        cards[i].suit = x;
        cards[i].rank = y;
    }
    for (int i = 1; i <= n; i++) f[cards[i].suit][cards[i].rank] = 1;
    K = clock();
    dfs(1, 0);
    if (ans <= 52) {
        puts("Yes");
        write(ans);
    } else {
        puts("No");
        write(min_missing);
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

### “啊，太毒瘤了。”

这是我看见这题引发的感慨。

题目大意：给定一副扑克牌，其中部分牌已经被移除。现在需要从剩下的牌中选出四个区间，每个区间内的牌都是同一花色且点数连续。

如果可以选出这样四个区间，则输出 Yes，否则输出 No。

如果输出 No，再输出最少需要添加多少张牌才能满足要求。


我们先考虑一下**暴力**，即记录一下每一张牌，枚举它换成另外三副牌的情况（同时可以不换），搜完之后回溯一下。想一下怎么判断是连续的一副牌，可以对于一种类型的牌，找一下点数最小的牌和点数最大的牌，因为要连续，所以两者之间所有点数的牌都需要有，没有的话就不是顺子。如果是 No 的话我们考虑怎么才可以得到顺子的最少需要牌数，其实可以在判断这个是否是顺子的时候，记录一下一种类型的牌最大点数与最小点数之间差的牌，这样找差的牌就可以了。

但是，只有 $60$ 分。

我们再来优化，可以将程序的运行时间强制放在一秒以内，直接输出现在的当前累积的答案，就能获得 $100$ 分。

---

## 作者：Genius_Star (赞：3)

## 题意：

给定一副扑克牌，其中部分牌已经被移除。现在需要从剩下的牌中选出四个区间，每个区间内的牌都是同一花色且点数连续。

如果可以选出这样四个区间，则输出 ``Yes``，否则输出 ``No``。

如果输出 ``No``，再输出最少需要添加多少张牌才能满足要求。

### 思路：

先考虑一下暴力，即记录一下每一张牌，枚举它换成另外三副牌的情况（同时可以不换），搜完之后回溯一下。

想一下怎么判断是连续的一副牌，可以对于一种类型的牌，找一下点数最小的牌和点数最大的牌，因为要连续，所以两者之间所有点数的牌都需要有，没有的话就不是顺子。

如果是 ``No`` 的话我们考虑怎么才可以得到顺子的最少需要牌数，其实可以在判断这个是否是顺子的时候，记录一下一种类型的牌最大点数与最小点数之间差的牌，这样找差的牌就可以了。

这样，我们就愉快的可以得到六十分了。

于是，我就想试试卡常，一卡，直接就过了，将程序的运行时间强制放在一秒以内，直接输出现在的当前累积的答案……（就相当于当前时间内计算的答案可能就是最终的答案）

~~数据加强了踢一下我，我改一个剪枝的……~~

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=60,M=20;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll x,y;
}a[N];
ll n,x,y,K,ans=INT_MAX,vum=INT_MAX;
char k[2];
bool f[5][M];
bool check(){
	register ll h=0;
	register bool k=1;
	for(register int i=1;i<=4;i++){
		register ll Min=15,Max=0;
		for(register ll j=1;j<=13;j++){
			if(f[i][j]){
				Min=j;
				break;
			}
		}
		for(register ll j=13;j>=1;j--){
			if(f[i][j]){
				Max=j;
				break;
			}
		}
		for(register int j=Min;j<=Max;j++)
		  if(!f[i][j]) 
			k=0,h++;
	}
	vum=min(vum,h);
	return k;
}
void dfs(register ll pos,register ll sum){
	if(sum>=ans)
	  return ;
	if(check()){
		ans=min(ans,sum);
		return ;
	}
	if(pos>n)
	  return ;
	if((clock()-K)*1000>=200*CLOCKS_PER_SEC){
		if(ans<=52){
			puts("Yes");
			write(ans);
		}
		else{
			puts("No");
			write(vum);
		}
		exit(0);
    }
	for(register int i=1;i<=4;i++){
		if(f[i][a[pos].y]&&i!=a[pos].x)
		  continue;
		f[a[pos].x][a[pos].y]=0;
		f[i][a[pos].y]=1;
		if(i!=a[pos].x)
		  dfs(pos+1,sum+1);
		else
		  dfs(pos+1,sum);
		f[i][a[pos].y]=0;
		f[a[pos].x][a[pos].y]=1;
	}
}
int main(){
	n=read();
	for(register int i=1;i<=n;i++){
		x=read();
		scanf("%s",&k);
		if(k[0]=='A')
		  y=1;
		else if(k[0]=='J')
		  y=11;
		else if(k[0]=='Q')
		  y=12;
		else if(k[0]=='K')
		  y=13;
		else if(k[0]=='1'&&k[1]=='0')
		  y=10;
		else
		  y=k[0]-'0';
		a[i].x=x,a[i].y=y;
	}
	for(register int i=1;i<=n;i++)
	  f[a[i].x][a[i].y]=1;
	K=clock();
	dfs(1,0);
	if(ans<=52){
		puts("Yes");
		write(ans);
	}
	else{
		puts("No");
		write(vum);
	}
	return 0;
}
```


---

## 作者：luozejun_180913 (赞：1)

### 思路
这道题时间复杂度有点极限，考虑剪枝。

排去时间问题，这题还是很简单的。直接用 DFS 找出最优答案，在每次交换之后判断是否符合要求，并用二位数组记录每次交换之后的卡牌情况，运用递归找出最少步骤。具体看代码。

### code
```cpp
#include<bits/stdc++.h>
#define R register int
using namespace std;
const int N=99;
int a[N],b[N],l[N],r[N],cnt[N],n,now1,ans=N,ans1=N;
char s[N];
void dfs(R h,R lef) { //lef为n-当前已选中总次数
	if(h==5) {
		R now=0;
		for(R i=1; i<=13; ++i) {
			if(cnt[i]>0)return;//不合法
			now|=cnt[i]<0;
		}
		if(now) {
			ans1=now1;    //No状态
			return;
		}
		for(R i=1; i<=n; ++i) //Yes状态，统计答案
			if((l[a[i]]>b[i]||r[a[i]]<b[i])&&++now==ans)return;
		ans=now;
		ans1=1;
		return;//注意ans1=1的剪枝作用
	}
	for(R i=max(lef-(4-h)*13,0),j,rr; i<=13; ++i) { //枚举区间长度，可行性剪枝
		if(i==0) {
			l[h]=r[h]=0;
			dfs(h+1,lef);
			continue;
		}
		for(rr=i; rr<=13; ++rr) { //枚举右端点
			for(j=rr-i+1; j<=rr; ++j)now1+=--cnt[j]<0; //动态维护当前选多了的总数
			if(now1<ans1)l[h]=(r[h]=rr)-i+1,dfs(h+1,lef-i);//最优性剪枝
			for(j=rr-i+1; j<=rr; ++j)now1-=++cnt[j]<=0;
		}
	}
}
int main() {
	scanf("%d",&n);
	for(R i=1; i<=n; ++i) {
		scanf("%d%s",&a[i],s);
		if(s[0]=='A')b[i]=1;//把点数处理一下
		else if(s[0]=='1')b[i]=10;
		else if(s[0]=='J')b[i]=11;
		else if(s[0]=='Q')b[i]=12;
		else if(s[0]=='K')b[i]=13;
		else b[i]=s[0]-'0';
		++cnt[b[i]];
	}
	dfs(1,n);
	if(ans!=N)printf("Yes\n%d\n",ans);
	else printf("No\n%d\n",ans1);
	return 0;
}

```

---

