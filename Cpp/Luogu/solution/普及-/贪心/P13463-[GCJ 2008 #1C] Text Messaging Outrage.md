# [GCJ 2008 #1C] Text Messaging Outrage

## 题目描述

我的一位亲密朋友 Loony 教授冲进了我的办公室。他满脸通红，看起来非常生气。他张口就说：“该死的手机制造商。我只是想发条短信，结果打一行字花了我十多分钟！”我试图安慰他：“到底怎么了？为什么花了你这么久？”他继续说道：“你难道没发现吗？！他们把字母排得一团糟？为什么 ‘s’ 是它所在按键的第 4 个字母？还有 ‘e’？为什么不是它所在按键的第一个字母？我得按 ‘7’ 四次才能打出一个 ‘s’？这太疯狂了！”

“冷静点，我的朋友，”我说，“这种方案已经用了很久了，甚至在短信发明之前就有了。他们不得不保持这种方式。”

“这不是借口，”他的脸越来越红。“是时候改变这一切了。一开始就是个愚蠢的主意。既然如此，为什么只在 8 个按键上放字母？为什么不用全部 12 个？为什么还必须是连续的？”

“呃……我……不知道……”我回答。

“好了，就这样。这些人显然不称职。我相信一定有人能想出更好的方案。”

我能看出来，他就是那种只会抱怨问题，却从不真正尝试解决问题的人。

在本题中，你需要设计一种最优的字母分配方案，使得输入一条消息所需的按键次数最少。你将得到可用按键数、每个按键最多可放的字母数、字母表的总字母数，以及每个字母在消息中出现的频率。字母可以任意分配到任意按键，顺序也可以任意。每个字母只能出现在一个按键上。字母表可能超过 26 个字母（不一定是英语）。

作为参考，目前手机键盘的布局如下：

```
按键 2：abc
按键 3：def
按键 4：ghi
按键 5：jkl
按键 6：mno
按键 7：pqrs
按键 8：tuv
按键 9：wxyz
```

第一次按某个按键会输入该键的第一个字母，每多按一次就输入下一个字母。例如，要输入单词 “snow”，你需要按 “7” 四次，再按 “6” 两次，再按 “6” 三次，最后按 “9” 一次。总共需要按键 10 次。

## 说明/提示

**限制条件**

- $P \times K \geq L$
- $0 \leq$ 每个字母的出现频率 $\leq 1000000$

**小数据集（5 分，测试集 1 - 可见）**

- $1 \leq N \leq 10$
- $1 \leq P \leq 10$
- $1 \leq K \leq 12$
- $1 \leq L \leq 100$

**大数据集（10 分，测试集 2 - 隐藏）**

- $1 \leq N \leq 100$
- $1 \leq P \leq 1000$
- $1 \leq K \leq 1000$
- $1 \leq L \leq 1000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3 2 6
8 2 5 2 4 9
3 9 26
1 1 1 100 100 1 1 1 1 1 1 1 1 1 1 1 1 10 11 11 11 11 1 1 1 100```

### 输出

```
Case #1: 47
Case #2: 397```

# 题解

## 作者：Sweet_2013 (赞：11)

先从大到小排序，然后将出现频率高的字母放在按键的前面位置，这样高频字母需要的按键次数可以最少。最后我们发现本题用了贪心。

```
#include<bits/stdc++.h>
using namespace std;
int n,p,k,l;
long long a[1005];
int main() {
    cin>>n;
    for(int q=1;q<=n;q++) {
        cin>>p>>k>>l;
        for(int i=1;i<=l;i++)cin>>a[i];
        sort(a+1,a+l+1,greater<long long>()); //greater<long long>() 用来从大到小排序。
        long long ans=0;
        for(int i=1;i<=l;i++) {
            int j=(i-1)/k+1;//计算按键次数。
            ans+=a[i]*j;
        }
        cout<<"Case #"<<q<<": "<<ans<<"\n";
    }
}
```

---

## 作者：GeorgeDeng (赞：3)

看起来还没有题解。

这道题就是让我们按照最优的排列键盘的方式，使得按下的键最少。

显然，我们要把出现次数从大到小排序。为什么呢？因为出现次数多的要尽量放在上面，避免出现次数多的放在最下面，导致按键次数暴涨。然后就是把每个键 “放” 上去。具体怎么放呢？我们用两个变量 $now,nowy$ 记录当前的键放在第 $nowy$ 层的第 $now$ 个位置。每次答案加上出现次数乘上 $nowy$，然后把 $now \larr now+1$。当  $now>k$ 的时候，我们就应该放下一层了，$now \larr 1,nowy \larr nowy+1$。最后输出答案即可。

我们发现这道题与 $p$ 一点关系没有，因为如果 $p$ 很小，那么这么多键连放的地方都没有，只有 $p$ 足够大，才有位置。而我们不需要考虑这个问题，因为 $p$ 已经足够大了，我们没有必要考虑。

代码如下：

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

int p,k,l;
int a[1005];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int _;
    cin>>_;
    int test_case = 1;
    while(_--){
        cout<<"Case #"<<test_case<<": ";
        cin>>p>>k>>l;
        for(int i = 1;i<=l;i++){
            cin>>a[i];
        }
        sort(a+1,a+1+l,greater<int>() );//从大到小排序
        int ans = 0;
        int now = 1;
        int now_y = 1;//如上
        for(int i = 1;i<=l;i++){
            ans+=now_y*a[i];//统计答案
            now++;
            if(now>k) now_y++,now = 1;
        }
        cout<<ans<<endl;//输出答案
        test_case++;
    }
    return 0;
}
```

---

## 作者：furina_yyds (赞：1)

# 题解：P13463 \[GCJ 2008 #1C] Text Messaging Outrage

这是一道贪心水题。

## 思路

要使得总次数最少，优先要将频率高的字母放在按键前面，所以可以将字母按频率排序，前 $1 \sim k$ 大的字母放在所有按键的第一个，前 $k+1 \sim 2k$ 大的字母放在所有按键的第二个，以此类推。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n, p, k, l, a[1005];
long long ans;
int main(){
	scanf("%d", &n);
	for(int _ = 1; _ <= n; _++){
		scanf("%d%d%d", &p, &k, &l);
		ans = 0;
		for(int i = 1; i <= l; i++){
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + l + 1, greater<int>());
		for(int i = 1; i <= l; i++){
			ans += a[i] * ((i + k - 1) / k);
		}
		printf("Case #%d: %lld\n", _, ans);
	}
	return 0;
}
```

---

## 作者：alice_c (赞：1)

## 思路

很简单的一道题。

考虑贪心。我们可以把 $a$ 从大到小排序，把出现最多次数的前 $k$ 个字符放在 $k$ 个按键的第一位，以此类推。然后计算每一个字符需要按几次按键，即 `((i-1)/k+1)*a[i]`，并求和。

注意，答案 `ans` 需要开 `long long`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,p,k,l,a[1005];
int main()
{
    cin >> n;
    for(int t=1;t<=n;t++){
        cin >> p >> k >> l;
        for(int i=1;i<=l;i++)
            cin >> a[i];
        sort(a+1,a+l+1,greater<int>());
        long long ans=0;
        for(int i=1;i<=l;i++)
            ans+=((i-1)/k+1)*a[i];
        printf("Case #%d: %lld\n",t,ans);
    }
}
``````

---

## 作者：unick (赞：0)

~~辣么简单的一道题居然没人写题解？可惜可惜。~~
# 题意解析
给定 $n$ 组输入，每组输入两行,第一行输入三个整数 $P$、$K$、$L$，第二行输入 $L$ 个整数，问怎么样才能使 Loony 教授用最少的按键次数打出所有字母。
# 思路描述
不难看出这是贪心的题目，先利用降序将原数组排序，然后只需要将次数较多的字母优先考虑即可解决此题。
# *Code*
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,num;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--){
		++num;
		int p,n,m,cnt=0,ans=0;
		int a[1005];
		cin>>p>>n>>m;
		for(int i=1;i<=m;i++)
			cin>>a[i];
		sort(a+1,a+m+1,cmp);
		int i=1;
		while(i<=m){
			++cnt;
			for(int j=1;j<=n;j++){
				ans+=a[i++]*cnt;
				if(i>m)break;
			}
		}
		cout<<"Case #"<<num<<": "<<ans<<endl;
	}
 	return 0;
}


```
求过求赞 QAQ

---

## 作者：_ChronicleA_ (赞：0)

### 题外话
我曾有幸用过一段时间的按键手机，发短信时一句话真的要打好长一段时间......没想到这个题目直戳心中痛点......

---
### 题目要求
给出 $N$ 组数据，分别是最多放置的字母数量 $P$，可用按键数量 $K$ 和字母总数量 $L$。接下来是字母使用频率。求最少的按键次数。

---
### 基本思路
使用频率越高的字母，当然要优先安排在各个按键尽量靠前的位置。于是我们可以先将数组进行降序排序，然后依照题意，每 $K$ 个字母依次放在各个键位上，用一个变量 $cnt$ 来记录放到了第几个。最后将按键次数加起来，输出即可。

---
### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
const int N=1e6+10;
int p,k,l,a[N];
bool cmp(int a,int b)
{
	return a>b;
}
int num;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>p>>k>>l;
		for(int i=1;i<=l;i++)cin>>a[i];
		sort(a+1,a+1+l,cmp);//9 8 5 4 2 2
		int cnt=1,ans=0,len=1;//17+18+12
		for(int i=1;i<=l;i++)
		{
//			cout<<a[i]<<" ";
			ans=ans+a[i]*cnt;
//			cout<<a[i]<<"*"<<cnt<<"+";
			len++;
			if(len>k)cnt++,len=1;
		}
//		cout<<endl;
		cout<<"Case #"<<++num<<": "<<ans<<endl;
	}
}
```

---

完结撒花~

---

## 作者：Xjj2013_0405 (赞：0)

##  思路 ##
这题思路比较简单。先输入，然后发现题目都告诉我们每个字母出现的次数了，那我们自然要把次数高的往前放。这里有一个误区：我们要先把每个按键的第一个位置都放满，在放第二个位置。而不是先放满第一个按键再放第二个。所以我们先排序（降序），之后用当前序号除以按键总数算出位置，再在总次数中加上 位置乘该字母出现的次数，最后按格式输出就行了。
## 代码 ##
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//个人习惯 
const int N=1e3+5;
int n,p,k,l,sum=0,a[N];//sum为次数 
bool cmp(int x,int y){
	return x>y;//降序排序判断 
}
signed main(){
	cin>>n;
	for(int t=1;t<=n;t++){
		memset(a,0,sizeof a);
		sum=0;//多测清空 
		cin>>p>>k>>l;
		for(int i=0;i<l;i++) cin>>a[i];// 输入 
		sort(a,a+l,cmp);//降序排序
		for(int i=0;i<l;i++) sum+=a[i]*(i/k+1);//次数计算，每次加上 出现次数*该字母在按键中的位置（见思路） 
		cout<<"Case #"<<t<<": "<<sum<<"\n";//格式输出 
	}
	return 0;//完结撒花 
}
```

---

## 作者：LTL_MJJ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P13463)
# 解析
观察题目，~~和标签~~不难发现：

- 一个字母出现频率越大，越应该把它放在一个按键的前面。比如设有两个字母的出现频率分别为 $N,M$，所处的按键位置分别为 $N_{1},M_{1}$，且有 $N \lt M$，则按的次数为 $N \times N_{1} + M \times M_{1}$，显然减小 $M_{1}$ 的值比减小 $N_{1}$ 的值要划得来（按得次数下降的快）。

为了保证尽量使频率大的字母在按键前面，我们应该先把所有按键的第一层先填满，然后是第二层、第三层……，不必使一个按键填满。（数据范围保证按键填的下所有字母）

这样我们只需给字母的频率排序即可，不需要有字母。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[1145],cnt;
bool cmp(int x,int y){
	return x>y;//从大到小 
}
int main(){
	cin >> n;
	cnt=n;//序号 
	while(n--){
		int p,k,l;
		cin >> p >> k >> l;
		memset(a,0,sizeof(a));//不要忘记初始化 
		for(int i=1;i<=l;i++) cin >> a[i];
		sort(a+1,a+l+1,cmp);
		long long ans=0,v=0,flag=0;
		for(int i=1;i<=p;i++){
			for(int j=1;j<=k;j++){
				ans+=a[++v]*i;//字母频率*所在位置 
				if(v==l){//v记录所填字母序号 当第v个字母填完后，跳出 
					flag=1;
					break;
				}
			}
			if(flag==1) break;
		}
		cout << "Case #" << cnt-n << ": " << ans << "\n";
	}
	return 0;
}
```
[记录](https://www.luogu.com.cn/record/227298028)

---

## 作者：liketaem (赞：0)

# 题目分析
这是一道~~贪心~~的题目。
# 思路
### 1. 题目解释
我们需要将字母分配到按键上，每个按键最多可以放 $P$ 个字母。字母的按键次数取决于其在按键上的位置。例如，第一个字母按一次，第二个字母按两次，依此类推。
### 2. 贪心思路
为了最小化总按键次数，应该将出现频率最高的字母分配到按键的第一个位置，次高频的字母分配到按键的第二个位置，依此类推。
### 3. 实现
- 统计每个字母出现的频率
- 将所以字母按频率大到小排序
- 将所有次数乘以按键要按次数，求出答案。
# 代码
```cpp
#include<bits/stdc++.h>
#define ri register int
#define int long long
#define run_fast ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
signed main() {
	int T;
	cin >> T;
	for (ri x = 1; x <= T; ++x) {
		int P, K, L;
		cin >> P >> K >> L;
		vector<long long> freq(L);
		for (ri i = 0; i < L; ++i) cin >> freq[i];
		sort(freq.rbegin(), freq.rend());
		long long total = 0;
		for (ri i = 0; i < L; ++i) {
			int press = (i / K) + 1;
			total += freq[i] * press;
		}
		cout << "Case #" << x << ": " << total << endl;
	}
	return 0;
}
```

---

## 作者：b_donk (赞：0)

### 题目大意  
自定义手机键盘字母布局，将字母分配到按键上，使得输入给定频率的字母序列所需按键次数最少。
### 题目思路  
采用贪心算法，将频率最高的字母分配到按键次数最少的位置（即按键上的第一个位置），最后答案就为所有字母频率乘以其按键次数的总和。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long // 防止数据溢出
main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t ++) {
        int P, K, L; // P:按键最大字母数 K:按键数量 L:字母总数
        cin >> P >> K >> L;
        vector<int> f(L); // 字母频率数组
        for (int i = 0; i < L; i ++) {
            cin >> f[i];
        }
        sort(f.rbegin(), f.rend()); // 将频率降序排序
        int res = 0; // 总按键次数
        for (int i = 0; i < L; i ++) {
            int pos = i/K + 1; // 计算字母所在位置
            res += f[i] * pos; // 累加当前字母的总按键次数
        }
        cout << "Case #" << t << ": " << res << '\n';
    }
    return 0;
}
```
### [AC记录](https://www.luogu.com.cn/record/227277393)

希望文章能够帮助到你。

---

## 作者：New_Void (赞：0)

## [P13463 [GCJ 2008 #1C] Text Messaging Outrage](https://www.luogu.com.cn/problem/P13463)

### 思路

这道题是典型的贪心问题。由于高频字符是要打的最多的，所以我们要尽量的让高频字符出现在一个按键的靠前位置，所以我们需要先将数组进行一个倒序排序。因为有不止一个按键，并且要保证高频率字符在前面，所以我们要尽量让排序好频率的字符进行平均分配。最后每次都将答案加等于字符所在的按键的位置乘按键的频率，就是最终答案。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int read(){
    int k=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') k=k*10+c-'0',c=getchar();
    return k*f;
}
signed main(){
    int N=read();
    for (int i=1;i<=N;i++){
        int P,K,L;
        P=read(),K=read(),L=read();
        int a[L];
        for (int i=0;i<L;i++) a[i]=read();
        sort(a,a+L,greater<int>());
        long long ans=0,cnt=0,idx=1;//一定要开long long
        for (int j=0;j<L;j++){
            if (cnt==K) idx++,cnt=0;
            ans+=idx*a[j];
            cnt++;
        }
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    return 0;
}

```

---

## 作者：HP_Serenity (赞：0)

贪心题。策略是将高频字母优先分配到按键的前序位置。我们先将字母按频率降序排序；之后高频字母优先占用按键第 $1$ 位，即按键 $1$ 次，以此类推。那么总按键次数便是每个字母频率乘上其所在位置的按键次数，例如第 $i$ 个字母的按键次数为 $\lceil \frac{i}{k} \rceil$。

```c++
#include <bits/stdc++.h>
using namespace std;
int f[1005], n, p, k, l;
int main() {
    scanf("%d", &n);
    for(int c=1; c<=n; c++) {
        scanf("%d%d%d", &p, &k, &l);
        for(int i=1; i<=l; i++) scanf("%d", &f[i]);
        sort(f+1, f+l+1, greater<int>());
        long long ans = 0;
        for(int i=1; i<=l; i++) ans += 1LL*f[i]*((i-1)/k+1);
        printf("Case #%d: %lld\n", c, ans);
    }
    return 0;
}
```

---

## 作者：Zjb13927701829 (赞：0)

# P13463 [Text Messaging Outrage](https://www.luogu.com.cn/problem/P13463) 题解
## 题目简述
我们要在键盘上打出 $l$ 个字母，第 $i$ 个字母出现的频率为 $a_i$，键盘布局为宫格式，有 $k$ 个格子，每个格子最多可以放置 $p$ 个字母。

同一个字母只能放在一个格子里面，每个字母的按键次数取决于它在按键上的位置（第 $i$ 个位置要按 $i$ 次）。

问：在最优布局下，要按多少次键才能打出我们要打的字母？
## 思路与方法
- **贪心策略‌**：将高频出现的字母优先分配到按键**前面**的位置（即按键次数少的位置）。\
  具体做法是将字母按频率进行**降序排序**，然后从前往后依次分配到各个按键的每个位置。
- **分层分配‌**：将排序后的字母分成若干层，每层包含 $k$ 个字母（最后一层可能不足 $k$ 个），第 $i$ 层的字母分配到所有按键的第 $i$ 个位置。\
  这样能确保**高频字母**的按键**次数最少**。
- 每个字母的按键次数为 $i \div k + 1$，其中 $i$ 是当前的索引（从 $0$ 开始），$k$ 是可用的按键数。
- 最后，**累加**所有字母的按键次数（频率 $\times$ 按键次数）就结束了。
## [AC](https://www.luogu.com.cn/record/226927581) Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int cn=1;cn<=n;cn++){
        long long p,k,l;
        cin>>p>>k>>l;
        int a[l+10];
        for(int i=0;i<l;i++){ //输入数据
            cin>>a[i];
        }
        sort(a,a+l,greater<long long>()); //降序排序
        long long tp=0;
        for(int i=0;i<l;i++){//计算按键数、累加
            long long kp=(i/k)+1; 
            tp+=a[i]*kp;
        }
        cout<<"Case #"<<cn<<": "<<tp<<'\n'; //输出结果
    }
    return 0;
}
```

---

## 作者：lcliruiyan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13463)

## 题目大意

给出 $N$ 组测试数据，每组数据给出每个按键最多可放的字母数 $P$、可用按键数 $K$、字母表中字母总数 $L$ ，再给出 $L$ 个字母各自出现的频率，问最优排列下最少要按多少次按键。

## 题目思路

观察样例，可以发现，每个字母要按的次数就是这个字母在按键上排的位置。要使按下的次数最少，就要让出现频率越高的字母排在每一个按键的越前面。因此，这道题可以用贪心算法来做。

我们可以用一个结构体数组维护每个字母的出现次数和编号，对这个结构体数组进行排序，让出现次数高的字母排在前面。

接着，我们再用 $K$ 个动态数组模拟 $K$ 个按键，按顺序将字母放到按键上，每个字母要按的次数就可以很容易地算出来了。

最后，将每个字母要按的次数加起来，就是最终答案了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,p,k,l,x;
struct word
{
    int x,k;
}a[1005];
bool cmp(word a,word b)//将结构体数组按出现次数从大到小排序
{
    return a.k>b.k;
}
int main()
{
    cin>>T;
    for(int t=1;t<=T;t++)
    {
        cin>>p>>k>>l;
        for(int i=1;i<=l;i++)
            cin>>a[i].k,a[i].x=i;//存储每个字母的编号和出现位置
        sort(a+1,a+l+1,cmp);
        vector<int>s[k+1];
        long long ans=0;
        for(int i=0;i<l;i++)
            s[i%k+1].push_back(a[i].x),ans+=s[i%k+1].size()*a[i+1].k;//计算每个字母要按的次数
        cout<<"Case #"<<t<<": "<<ans<<endl;//输出，注意不要忘了Case
    }
    return 0;
}
```

---

## 作者：TCY1234567 (赞：0)

### 题解

看到这道题第一眼就是贪心。

我们发现，出现字母的次数越多，我们就越应该把它放在前面，所以直接对数组排序，越大的放在前面，也就是将次数 $ \times 1$，以此类推，统计答案即可。

### 正确代码

```cpp
#include <bits/stdc++.h>
#define int long long//十年OI一场空，不开 long long 见祖宗。
using namespace std;
int a[1000005];
signed main()
{
	int t;
	scanf("%lld",&t);
	for(int i=1;i<=t;i++)
	{
		int n,m,k;
		scanf("%lld%lld%lld",&n,&m,&k);
		for(int j=1;j<=k;i++) scanf("%lld",&a[j]);
		sort(a+1,a+k+1);
		int cnt = 1,qwq = 0,ans = 0;
		for(int j=k;j>=1;i--)
		{
			ans+=a[j]*cnt;
			qwq++;
			if(qwq==m)//统计现在应该分配到第几个键了
			{
				cnt++;
				qwq = 0;
			}
		}
		printf("Case #%lld: %lld\n",i,ans);//输出
	}
}//请不要直接复制粘贴，谢谢
```

---

## 作者：csxx601cjy (赞：0)

### 题意
已知每个按键最多字母数（$P$）、可用按键数（$K$）、字母总数（$L$），并且要输入某个按键的第 $i$ 个字母，就要按 $i$ 下。给出要打的所有字母的出现次数，可以随意构造键盘布局，求打出所有字母的最少按键次数。
### 思路
考虑贪心，因为字母出现次数越多的，打字次数也越多。给这些字母放到键盘上更好打的位置，最后就能保证答案最优。

先从大到小排序，给出现频率前 $K$ 高的字母排到所有按键的第 $1$ 位，前 $K+1\sim 2\times K$ 的字母排到所有按键的第 $2$ 位，以此类推。

因为题目保证 $P\times K\ge L$，所以不用担心排不下。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,k,l,a[1010]; //a数组记录每种字母的出现次数
int main(){
    cin>>n;
    for(int t=1;t<=n;t++){ //t是测试用例编号
        cin>>p>>k>>l;
        for(int i=1;i<=l;i++)cin>>a[i]; //读入字母出现次数
        sort(a+1,a+l+1,greater<int>()); //从大到小排序
        long long ans=0; //一定记得开long long
        for(int i=1;i<=l;i++)
          ans+=a[i]*((i-1)/k+1); //(i-1)/k+1是第i个字母按几下才能打出来
        printf("Case #%d: %lld\n",t,ans); //按照格式输出
    }
    return 0;
}
```

---

