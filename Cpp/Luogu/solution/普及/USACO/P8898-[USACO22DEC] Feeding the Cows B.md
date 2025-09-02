# [USACO22DEC] Feeding the Cows B

## 题目描述

Farmer John 有 $N(1 \le N \le 10^5)$ 头奶牛，每头奶牛的品种是更赛牛（Guernsey）或荷斯坦牛（Holstein）之一。她们沿水平方向排成一行，奶牛们占据的位置编号为 $1 \cdots N$。

由于奶牛们都饿了，FJ 决定在 $1 \cdots N$ 中的某些位置上种植草地。更赛牛和荷斯坦牛喜欢不同类型的草，所以如果 Farmer John 决定在某个位置种草，他必须选择种植更赛牛喜欢的草或荷斯坦牛喜欢的草——他不能在同一个位置同时种两种草。种植的每一片草地都可以喂饱数量不限的相应品种的奶牛。 

每头奶牛愿意移动至多 $K(0 \le K \le N-1)$ 个位置以前往一个草地。求出喂饱所有奶牛所需种植的最小草地数量。此外，输出一种使用最小草地数量喂饱所有奶牛的种植方案。任何满足上述条件的方案均视为正确。 

## 说明/提示

### 样例 1 解释

注意对于某些子测试用例，存在多种可通过的方案使用最小数量的草地。例如，在第四个子测试用例中，以下是另一个可以通过的答案：

$$\texttt{.GH..}$$

这个方案在第二个位置种植一块喂饱更赛牛的草地以及在第三个位置种植一块喂饱荷斯坦牛的草地。这使用了最小数量的草地并确保了所有奶牛都在她们喜欢的草地的 $3$ 个位置以内。

### 测试点性质

- 测试点 $2-4$ 满足 $N \le 10$。
- 测试点 $5-8$ 满足 $N \le 40$。
- 测试点 $9-12$ 满足 $N \le 10^5$。 

## 样例 #1

### 输入

```
6
5 0
GHHGG
5 1
GHHGG
5 2
GHHGG
5 3
GHHGG
5 4
GHHGG
2 1
GH```

### 输出

```
5
GHHGG
3
.GH.G
2
..GH.
2
...GH
2
...HG
2
HG```

# 题解

## 作者：chlchl (赞：19)

AK 的第一场正式比赛，当然要庆祝一下。

这是 USACO 2022 铜组 T2，难度适中，有一定迷惑性。

## 做法
贪心地枚举。

我一开始想的是 DP。显然这个数据范围只能是线性状态，所以 $f_i$ 只能是前 $i$ 块草坪 / 前 $i$ 头牛的一些信息。

但无论如何，即使扩展到 $f_{i,0/1}$，都不好转移。其他的解法也不行，所以考虑一个类似贪心的东西。

可以知道，第 $i$ 块草坪可以满足 $[i-k,i+k]$ 这块区域。所以，我们记录两种草坪**当前分别可以满足的最远点**（记为 $nowh,nowg$）。

设第 $i$ 头牛吃的草种类为 $c$，如果 $c$ 类满足的最远点没到 $i$（即第 $i$ 个位置的牛吃不到草），我们就从 $\min(i+k,n)$ **往前**找一块未被填的草坪填上。

为什么从后往前找？因为这样可以满足尽量远的位置，尽可能地减少填的数量。

这个过程必定有解，因为只要每头牛底下都是它那个种类的草，一定能满足条件，所以不必担心无解。

可以证明，$nowh,nowg$ 只增不减。换言之，它们一旦到达 $n$，就不会再动了，最多扩展 $n$ 次，加上枚举每头牛的时间，总的时间复杂度是 $O(2n)$，也就是 $O(n)$。

可以发现这个东西跟 Manacher 和扩展 KMP 有异曲同工之妙。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int T, n, k;
char s[N], t[N];

int main(){
	scanf("%d", &T);
	while(T--){
		memset(t, 0, sizeof(t));
		scanf("%d%d", &n, &k);
		scanf("%s", s + 1);
		int ans = 0, nowh = 0, nowg = 0;
		for(int i=1;i<=n;i++)
			t[i] = '.';
		for(int i=1;i<=n;i++){
			if(s[i] == 'H' && nowh < i){
				for(int j=min(i+k,n);j;j--){
					if(t[j] == '.'){
						t[j] = 'H';
						ans++, nowh = j + k;
						break;
					}
				}
			}
			if(s[i] == 'G' && nowg < i){
				for(int j=min(i+k,n);j;j--){
					if(t[j] == '.'){
						t[j] = 'G';
						ans++, nowg = j + k;
						break;
					}
				}
			}
		}
		printf("%d\n", ans);
		printf("%s\n", t + 1);
	}
	return 0;
}
```


---

## 作者：guozhetao (赞：10)

## 思路
这是一道贪心题。我们先考虑更赛牛。


- 首先，一个草如果要供最多牛食用，它就要尽可能远离最远的牛，这样才能保证另一端更多的牛能吃到。这样一格草就能最多满足 $2 \times k + 1$ 只同一种牛的食用需求。

- 但是，如果第 $i$ 只牛已经靠近另一端，$i + k$ 已经超出了草地 $a$ 的距离，我们就将最后一格草放在草地的最末尾。这样就能放置最少的草地就能满足所有的更赛牛。

- 荷斯坦牛的方法显然也类似，要尽可能满足最多的牛，它要尽量放置在 $i + k$ 的位置，这保证和之前不会重复。因为 $i$ 位置的牛是唯一的，所以 $i + k$ 位置肯定没有被占用。

- 我们同时也要考虑荷斯坦牛最后一格草超出边境的问题。因为边界已经被更赛牛占用，我们就从 $a$ 到 $1$ 依次遍历找到空的格子放上就行了。一定要遍历到 $1$ 或者 $i - 1$，如果遍历到 $i$ 过不了样例的最后一小点（$a = i$）。

- 最后记得统计喂饱所有奶牛所需的最小草地数量，循环一遍即可。

## 代码
[AC记录](https://www.luogu.com.cn/record/97894456)
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<queue>
#include<map>
#include<algorithm>

using namespace std;

// 快读
inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while (ch < '0' or ch > '9'){if (ch == '-') f = -1;ch = getchar();}
	while (ch >= '0' and ch<='9'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}
int main() {
	int t = read();
	while(t--) {
    	//定义变量及输入
		int a = read(),k = read(),ans = 0;
		char c[100005],d[100005];
		for(int i = 1;i <= a;i++) cin>>c[i],d[i] = '.';
        //更赛牛
		for(int i = 1;i <= a;i++) {
			if(c[i] == 'G') {
                //未超出边界时
				if(i + k <= a) {
					d[i + k] = 'G';
				}
                //超出边界时
				else {
					d[a] = 'G';
				}
                //满足了牛的需求后记得加跳过已经满足的部分。
				i += 2 * k;	
			}
		}
        //荷斯坦牛
		for(int i = 1;i <= a;i++) {
			if(c[i] == 'H') {
            	////未超出边界时
				if(i + k < a) {
					d[i + k] = 'H';
				}
                //超出边界时
				else {
					for(int j = a;j >= 	1;j--) {
						if(d[j] == '.'){
							d[j] = 'H';
							break;
						}
					}
				}
				i += 2 * k;	
			}
		}
        //统计ans和输出
		for(int i = 1;i <= a;i++) if(d[i] != '.') ans++;
		printf("%d\n",ans);
		for(int i = 1;i <= a;i++) cout<<d[i];
		printf("\n");
	} 
    return 0;
}

```


---

## 作者：Svemit (赞：6)

###### [T1题解](https://www.luogu.com.cn/blog/503792/p8897-usaco22dec-cow-college-b-ti-xie)

###### [T3题解](https://www.luogu.com.cn/blog/503792/p8899-usaco22dec-reverse-engineering-b-ti-xie)
## [题目传送门](https://www.luogu.com.cn/problem/P8898)

## 分析

第二题也不是很难，题目中每头奶牛最多愿意移动 $K$ 个位置前往一个草地，也就是说一头牛能往左或者右走 $K$ 步，只要这其中有它吃的草那么我们就不必为了它去种一片草地。这个题的雏形就出来了，我们可以在满足它的前提下尽量往后放，能够顾及到后面的就可以了。

## 算法设计
  如果我们每判断一头牛都要扫一边它能够到的区间的话很显然这时的时间复杂度是 $O(nk)$ 的不能满足题目的数据范围，实测会超时 $3$ 个点，考虑如何去优化我们的贪心算法。经过一阵苦思冥想后发现为了后面的牛设的草地一定会在为了前面的牛设的草地后面，所以我们可以通过两个变量 $h$ 和 $g$ 来表示上一个草放的位置，只要与上一个草相差的位置不超过 $k$ 就能到，否则我们从它能到的区间从后往前扫到第一个空的位置。
  
###  AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k,cnt=0,h=-1,g=-1;//h表示上一个H放的位置，g同理 
		char s[100005];
		int a[100005]; //0表示. 1表示H 2表示G 
		bool vis[100005];
		memset(vis,false,sizeof(vis));
		memset(a,0,sizeof(a));
		cin>>n>>k>>s;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='H')
			{
				if(abs(i-h)>k||h==-1) //到不了或还没到就放一个 
				{
					for(int j=min(i+k,n-1);j>=max(i-k,0);j--)//从后往前找到第一个没有放的位置 
			        {
				        if(!vis[j])
				        {
					        a[j]=1;
					        vis[j]=true; //标记这个位置已经放了 
					        h=j; //更行h的值 
					        cnt++;
					        break; //找到一个就退出因为尽量往后放 
		         		}
		        	}
		    	}
			}
			if(s[i]=='G') //同理 
			{
				if(abs(i-g)>k||g==-1)
				{
					for(int j=min(i+k,n-1);j>=max(i-k,0);j--)
			        {
				        if(!vis[j])
				        {
					        a[j]=2;
					        vis[j]=true;
					        g=j;
					        cnt++;
					        break;
		         		}
		        	}
		    	}
			}
		}
		cout<<cnt<<"\n";
		for(int i=0;i<n;i++)
		{
			if(a[i]==0)
			  cout<<'.';
			if(a[i]==1)
			  cout<<'H';
			if(a[i]==2)
			  cout<<'G';
		}
		cout<<"\n";
	}
	
	return 0;
}

```


---

## 作者：zajasi (赞：6)

## 解题思路
跟第一题一样，也是贪心思路。我们考虑将每一棵草安在尽可能远的地方，先不要管超不超过范围。这样能将更多的牛考虑进去，从而将答案最小化。

然后，如果这样做的话，会有一部分的草种到界外。此时我们将在界外的草全部都移到界内空的位置，就可以了。
## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ball cout<<"\n"
int t;
int n, k;
string a;
main() {
	cin >> t;
	while (t--) {
		cin >> n >> k >> a;
		char ans[200020] = {};
		int a1 = 0;
		int a2 = 0;
		a = '%' + a;
		for (int i = 0; i < a.size(); i++) {
			if (a[i] == 'G') {
				if (i > a1) {
					ans[i + k] = 'G';
					a1 = i + k * 2;
				}
			} else {
				if (i > a2) {
					ans[i + k] = 'H';
					a2 = i + k * 2;
				}
			}
		}
		char s[100010];
		int l = 0;
		for (int i = n + 1; i <= n + 100010; i++) {
			if (ans[i] == 'G' || ans[i] == 'H') {
				l++;
				s[l] = ans[i];
			}
		}
		int count = 0;
		int id = n;
		while (count < l) {
			if (ans[id] != 'G' && ans[id] != 'H') {
				count++;
			}
			id--;
		}
//		cout << l << " " << id << " " << count;
//		ball;
		int now = 0;
		for (int i = ++id; i < a.size(); i++) {
			if (ans[i] != 'H' && ans[i] != 'G') {
				now++; 
				ans[i] = s[now];
			}
		}
//		cout << now;
//		ball;
		int tot = 0;
		for (int i = 1; i <= n; i++) {
			if (ans[i] == 'H' || ans[i] == 'G') tot++;
		}
		cout << tot;
		ball;
		for (int i = 1; i <= n; i++) {
			cout << (ans[i] != 'H' && ans[i] != 'G' ? '.' : ans[i]);
		}
		ball;
	}
	return 0;

}


```

---

## 作者：快斗游鹿 (赞：5)

考虑如何让方案最优。对于每只奶牛，为了保证它能被喂饱，它最多可以向右移动 $k$ 格，假设它移动了 $x$ 格，并在这个格子种上了它喜欢的草。而移动后，右边 $k$ 格中的同种奶牛也可以被喂饱，所以我们应当让 $x$ 尽量接近 $k$，才能使方案最优，那最好就是 $x=k$。但题目中提到，**他不能在同一个位置同时种两种草**，也就是说，可能更赛牛找到了最优的方案，但荷斯坦牛只能取次优的方案。所以对于每个已经种过草的格子，我们要打上标记。下一个还没被喂饱的奶牛如果移动 $x$ 格后遇到了一个种过草的格子，就将 $x$ 减一，直到遇到一个没种过草的格子。为什么不加一呢？因为我们还是需要保证当前这头牛能被喂饱的，否则我们的方案不一定最优。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,k,a[N],flag[N],kk[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	t=read();
	while(t--){
		n=read();k=read();int m=0;
		string s;cin>>s;
		for(int i=0;i<s.length();i++){
			if(s[i]=='G')a[i+1]=0;
			else a[i+1]=1;
			kk[i+1]=0;flag[i+1]=0;
		}
		for(int i=1;i<=n;i++){
			if(!flag[i]){
				int pre=i+k;if(pre>n)pre=n;
				while(kk[pre]){
					pre--;
				}
				kk[pre]=a[i]+1;if(a[pre]==a[i])flag[pre]=1;
				for(int j=i;j<pre;j++){
					if(a[j]==a[i])flag[j]=1;
				}
				for(int j=pre+1;j<=min(n,pre+k);j++){
					if(a[j]==a[i])flag[j]=1;
				}
			}
		}
		for(int i=1;i<=n;i++)if(kk[i])m++;
		cout<<m<<endl;
		for(int i=1;i<=n;i++){
			if(kk[i]==1)cout<<'G';
			else if(kk[i]==2)cout<<'H';
			else cout<<'.';
		}
		cout<<endl;
	}
	return 0;
}


```


---

## 作者：farfarqwq (赞：2)

## 前言

赛时没想出来，最后总分333pts，同学都AK穿了，wtcl

## 题意

选出最少的草地，使得所有同品种的奶牛离这些草地的任意一个距离不超过 $k$，并输出方案。

## Sol

考虑贪心，每个奶牛的草地尽量往后放这样可以够到更多其他的奶牛，所以放到 $i+k$。

当位置不超过 $n$ 时不会有重复（两种不同的草地放在了一起），但超过 $n$ 时是要放在 $n$ 内的，此时可以从 $n$ 往后找找到第一个空余的位置去放草地，不会没有地方放，因为触及这个奶牛所的草地（包括空闲的）不可能全是另一个品种（自己思考一下）。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 100005;
char s[N];
int n, k, a[N], ans[N];
int pos(int x) {//找到第一个可以放的位置
    x = min(n, x);//上界
    for (; ans[x]; x--);
    return x;
}
signed main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(ans, 0, sizeof(ans));//多测注意清空
        scanf("%d%d", &n, &k);
        scanf("%s", s + 1);
        int cnt = 0;
        int lst[2] = {-10000000, -10000000};//离他最近的草地
        for (int i = 1; i <= n; i++) {
            a[i] = (s[i] == 'H');//如果是'G'的话是0，'H'是1
            if (lst[a[i]] + k < i) {//没有草地够的到他了
                lst[a[i]] = pos(i + k);//为了省事所有的位置都跑一遍（其实只有最后两个会执行，总复杂度O(n)
                ans[lst[a[i]]] = a[i] + 1;//0表示空，1表示'G'，2表示'H'
                ++cnt;
            }
        }
        printf("%d\n", cnt);
        for (int i = 1; i <= n; i++) {
            printf("%c", !ans[i] ? '.' : (ans[i] == 1 ? 'G' : 'H'));//输出，可以写if
        }
        printf("\n");
    }
    return 0;
}
```

有问题可以私信或评论，请勿抄袭OvO。

---

## 作者：sunkuangzheng (赞：2)

**【题目分析】**

考虑贪心：对于每一种牛，都尽可能地把它对应的放地往后方。因为这样就可以省下前面的空间，答案一定不劣。剩下的问题就是如何处理最后的冲突。我们可以判断最后的点距离最后一次放置的点的距离是否小于 $k$，决定是否需要放置草地。

具体的实现细节见代码。

**【完整代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,t1,t2,n,k;
char c[100005],a[100005];
int main(){
    cin >> t;
    while(t--){
    	int ans = 0;
    	memset(a,0,sizeof(a));
    	cin >> n >> k;
    	cin >> c;
    	t1 = t2 = 999999;//t1/t2 记录还有几个位置需要放置草地
    	int l1 = -1e9,l2 = -1e9,l11=-1e9,l22=-1e9;//l1/l2 是最后一个读入的 G/H，l11/l22 是最后一次放置的位置
    	for(int i = 0;i < n;i ++){
    		if(c[i] == 'G' && i-l1 > k) t1 = min(k,t1),l11=i;
    		else if(c[i] == 'H' && i-l2 > k) t2 = min(k,t2),l22=i;
    		if(t1 == 0) a[i] = 'G',ans++,t1=999999,l1=i;//放置草地
    		else if(t2 == 0) a[i] = 'H',ans++,t2=999999,l2=i;
    		else a[i] = '.';
    		t1 --,t2 --;
		}
		int q = n-1;
		if(t1 <= k && l11-l1 > k){//判断是否需要放置
			while(a[q] != '.') q--;//寻找空地，避免冲突
			ans++,a[q] = 'G';
		}
		q = n-1;
		if(t2 <= k && l22-l2 > k){
			while(a[q] != '.') q--;
			ans++,a[q] = 'H';
		}
		cout << ans << endl << a << endl;
	}
    
	return 0;
}
```

---

## 作者：so_find_skind (赞：2)

一道很鬼的思维题啊。

前置：[贪心](https://blog.csdn.net/weixin_43736974/article/details/107122407)。

其实是一个不难的题。

介绍上面都说了，除了压轴题都不是很难。

它有一道很相近的题目，是2017年安徽省赛小学组的一道题，名字叫[安装饮水机](https://www.luogu.com.cn/paste/6si4qa9t)。

对于此省赛题可以写出不难的代码：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,p=-1,cnt;
struct f{
    int l,r;
}a[1005];
bool cmp(f a,f b){
    return a.r<b.r;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        a[i].l=max(0,x-y);
        a[i].r=x+y;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(a[i].l>p){
            p=a[i].r;
            ++cnt;
        }
    }
    cout<<cnt;
    return 0;
}
~~~
那么可以发现，USACO这一道题不同之处在于……两者会有冲突！

要让更多奶牛吃草，肯定在第 $i$ 个奶牛的时候尽量后放到最后一个力所能及的位置，即放到 $i+k$ 的位置，如果 $i+k>n$，那么放在第 $n$ 个位置，因为所有 $i$ 互不相同，所以除非放在第 $n$ 块草坪，否则没有冲突，如果冲突，就每次判断略前的位置，一直到一个未冲突的位置。

由于往后放，所以放过一次之后 $i$ 必须直接跳到 $i+2\times k$，否则懂得都懂。

可以发现代码差别不算大。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
string a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		cin>>a;
		b=" ";
		for(int i=1;i<=n;i++)
			b+='.';
		if(!k){
			cout<<n<<"\n"<<a<<"\n";
			continue;
		}
		a=" "+a;
		for(int i=1;i<=n;i++){
			if(a[i]=='G'){
				b[min(n,i+k)]='G';
				i+=2*k;
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i]=='H'){
				if(i+k<n){
					b[i+k]='H';
				}else{
					int l=n;
					while(b[l]=='G')
						--l;
					b[l]='H';
				}
				i+=2*k;
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			if(b[i]=='G' || b[i]=='H')
				++ans;
		cout<<ans<<"\n"<<b.substr(1,n)<<"\n";
	}
	return 0;
}

~~~

完结撒花！

---

