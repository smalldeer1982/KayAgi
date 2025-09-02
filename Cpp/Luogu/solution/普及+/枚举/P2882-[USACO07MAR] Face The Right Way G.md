# [USACO07MAR] Face The Right Way G

## 题目描述

Farmer John has arranged his N (1 ≤ N ≤ 5,000) cows in a row and many of them are facing forward, like good cows. Some of them are facing backward, though, and he needs them all to face forward to make his life perfect.

Fortunately, FJ recently bought an automatic cow turning machine. Since he purchased the discount model, it must be irrevocably preset to turn K (1 ≤ K ≤ N) cows at once, and it can only turn cows that are all standing next to each other in line. Each time the machine is used, it reverses the facing direction of a contiguous group of K cows in the line (one cannot use it on fewer than K cows, e.g., at the either end of the line of cows). Each cow remains in the same \*location\* as before, but ends up facing the \*opposite direction\*. A cow that starts out facing forward will be turned backward by the machine and vice-versa.

Because FJ must pick a single, never-changing value of K, please help him determine the minimum value of K that minimizes the number of operations required by the machine to make all the cows face forward. Also determine M, the minimum number of machine operations required to get all the cows facing forward using that value of K.

$N$ 头牛排成一列 $1 \le N \le 5000$。每头牛或者向前或者向后。为了让所有牛都面向前方，农夫每次可以将 $K$ 头连续的牛转向 $1 \le K \le N$，求使操作次数最小的相应 $K$ 和最小的操作次数 $M$。$F$ 为朝前，$B$ 为朝后。

请在一行输出两个数字 $K$ 和 $M$，用空格分开。

## 说明/提示

For K = 3, the machine must be operated three times: turn cows (1,2,3), (3,4,5), and finally (5,6,7)


## 样例 #1

### 输入

```
7
B
B
F
B
F
B
B```

### 输出

```
3 3```

# 题解

## 作者：Delva (赞：58)

###  贪心，枚举，差分
因为同一个点翻转两次就与没有翻转的效果相同了，因此我们有一个贪心策略为：

从左到右对于出现的每一个B翻转一次从当前点开始的区间，就能保证是最优解。

**样例的模拟：**

如果当前翻转的区间长度为3

粗体表示当前下标

**B** B F B F B B

(**B** B F) B F B B

**F** F B B F B B

F **F** B B F B B

F F **B** B F B B

F F (**B** B F) B B

F F **F** F B B B

F F F **F** B B B

F F F F **B** B B

F F F F (**B** B B)

F F F F **F** F F

F F F F F **F** F

F F F F F F **F**

但是我们会发现这样是n^2的，再枚举长度，就变为了n^3.因此，需要对区间翻转差分一下，总时间复杂度就是n^2的了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 10009;
int n;
bool A[maxn],B[maxn];
int main(){
	scanf("%d",&n);
	char ch;
	for(int i=1;i<=n;++i){
		cin>>ch;A[i]=ch=='B'?0:1;
	}
	int mincnt=0x7fffffff,anslen;
	for(int len=1;len<=n;++len){
		memset(B,0,sizeof B);
		bool b=0,flag=1;int cnt=0;//flag记录当前长度是否有解
		for(int i=1;i<=n;++i){//因为区间翻转只有状态0和1，所以用^代替+和-
			b^=B[i];//数组B为记录差分的数组
			if(!(A[i]^b)){//若当前位置为0
				if(i+len-1>n){flag=0;break;}//唯一的失败条件：一次翻转的长度大于剩余的长度
				b^=1,B[i+len]^=1;
				++cnt;
			}
		}
		if(flag){if(cnt<mincnt)mincnt=cnt,anslen=len;}
	}printf("%d %d\n",anslen, mincnt);
} 
```

---

## 作者：FallR (赞：41)

首先对于这个题目进行一波分析，题目中给出了一排牛，让我们对其进行转向，可以看到样例所给的数据：

**0 0 1 0 1 0 0**（0表示朝向后方，1表示朝向前方）

- 可以看到我们所进行的调整一定是从左端或者右端开始的（因为从中间开始对前后造成的影响是难以控制的）

- 在我们转牛的过程中对于每一段一定是从第一个 0 开始进行转向。拿样例来看：
		
0 0 1 0 1 0 0

从第一个零开始

我们会得到 ： 1 1 0 0 1 0 0

从第二个零开始

我们会得到 ： 0 1 0 1 1 0 0

***显然若是从第二个开始我们仍需要将前面的 0 进行转向***

当然也许有人会想  从第后面的零开始调整会影响到后方的数

那么我们再看


将从第二个零开始转向的转向两次： 1 0 1 1 1 0 0

反观第一个： 1 1 1 1 0 0 0

***从第二个零开始转向的仍需要处理前面的0 ，而且这样也会破坏之前的转向成果，所以相同次数的转向显然从第一个0开始更优***

然后我们可以想到从前往后依次遍历，一遇到 0 对之后的 k 个数据进行转向

**但写完之后发现会T**

回到数据分析之后我们发现此时我们使用的算法时间为 O(n *  n  * n)对于5000的数据来说显然很危险。

我们会想到把每次将后方 k 个元素的转向的时间改为 O(1) 此时我们可以思考

**对于每一个元素是否转向不用修它的值，而是进行标记之后判断它标记的值就可以知道它面向哪里**


然后 *标记* -> *你是否想到了差分*  

应该都学过吧（~~然而我当时听的时候就没学过~~）

这样我们设置一个 tage 来记录元素被标记的个数，每次遍历到 0 的时候把后面第 i+k-1 个元素标记一下 当我们遍历到那个元素时将 tage- - （~~相信后面的事情就不用我说了~~） 

还有一件事 当序列后面的元素数目不足k-1个的时候,判定这个k不成立直接跳过去 


（~~我&#￥A^^S%*&)%$#%^$%@ 因为这个90分 找了一个多小时的错~~）



```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5008;
int n,k,a[MAXN],f[MAXN<<1],tag,op,ans=MAXN;
int ansk,sum;
inline int read()
{
    register int x=0,f=1;
    char s;
    while((s=getchar())<'0'||s>'9')
    {
        s=='-'?f=-1:f=1;
    }
    x=s-'0';
    while((s=getchar())>='0'&&s<='9')
    {
        x=x*10+s-'0';
    }
    return x*f;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		char s;
		cin>>s;
		if(s=='B') a[i]=0;
		if(s=='F') a[i]=1;
	}
	for(register int k=1;k<=n;k++)
	{
		sum=0;tag=0;op=0;
		memset(f,0,sizeof(f));
		for(register int i=1;i<=n;i++)
		{
			
			if((a[i]+tag)%2==0)
			{
				if(i+k-1>n)	
				{
					op=1;
					break;
				}
				++sum;
				++tag;
				f[i+k-1]=-1;
			}
			if(f[i]==-1)
			{
				--tag;
				f[i]=0;
			}
		}
		if(op) continue;
		if(sum<ans)
		{
			ans=sum;
			ansk=k;
		}
	}
	printf("%d %d",ansk,ans);
	return 0;
}
```


---

## 作者：llzzxx712 (赞：31)

# P2882

## 题意简述

- 给定一个长度为 n 的 01 串。
- **选择一个 k 值**，每次一段长度为 k 区间将其中的数取反（0变成1，1变成0），最终使整个串变成 1 。
- 求出最小需要的操作次数和**在此条件下**最小的 k 。

## 题目分析

每次选择区间的长度是固定的，所以我们可以枚举 k ，将问题转化为 “每次一段长度为 k 区间取反，需要多少次操作可以将整个串变成1 。

显然对于每一个 0 我们都要对它至少操作一次，所以我们可以从左到右考虑，每次遇到 0 都将从这个 0 为左端点长度为 k 区间中的数取反，直到全变成1。**如果碰到 0 时此时到末尾的长度小于 k ，则无解**，考虑下一个 k 。

**为什么这样做是对的呢？**



假如有这样一个串 1$\color{red}\text{0}$$\color{gold}\text{10}$0…… , 我们枚举的 k = 2  ，那么要将最左边$\color{red}\text{红色的 0}$ 变成 1，应该将这个 0 和右边的$\color{gold}\text{金色的 10}$  取反而不去动它左边黑色的 1 。每一个状态下最左边的 0 我们都要去将它变成 1 （因为最终要把整个串变成 1），而因为我们是从左到右考虑的，所以它左边一定已经全部是 1 了 。

**同时，因为我们有两次枚举和一次区间修改，所以复杂度是 $O(n^3)$ 我们还要优化**

两次枚举不可避免，我们可以使用**差分**，将修改变成 $O(1)$ 。

## 代码思路

很多同学都是看懂了上面的思路但是到代码实现上就有些困难了，一个较大的问题就是差分如何实现。

我们可以维护一个 bool 变量 $"now"$ 来表示当前状态——是否翻转。易知翻转偶数次和不翻转是一样的，所以每次修改的时候只要异或上 $1$ 就可以了。而当前的的串（存在数组 a 中）的值就是 $a[i]$ 异或 $now$，每次差分时将 $now$和差分数组$cha[i+k]$修改 ,也就是现在翻转一下，到了位置 $i+k$ 的时候再改回来，等价于修改 $i$ 到 $i+k$ 的值。

## 易错点
- 每次枚举 k 的时候要将差分数组清0
- 注意先输出 k 值再输出 m 值
- 记得判断无解

## AC代码

内带详细注释帮助理解

```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
#define N 5010
int n,ansm=2100000000,ansk;
int a[N];//原串 
bool cha[N];//差分数组 
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		char ch;cin>>ch;
		if(ch=='F') a[i]=1;//读入，朝前的为 1 
	}
	for(int k=1;k<=n;k++){
		memset(cha,0,sizeof(cha));//易错点 1 
		int flag=1,tot=0,now=0;//tot 记录当前需要操作几次 
		for(int i=1;i<=n;i++){
			now^=cha[i];//每次操作前异或差分数组，也许这个点就是某次差分的末尾 
			if(a[i]^now==0){//碰到 0 ，进行操作 
				if(i+k-1>n){//无解 
					flag=0;
					break;
				}
				tot++;//记录答案 
				now^=1,cha[i+k]^=1;//差分修改 
			}
		}
		if(flag){
			if(tot<ansm){//更新答案 
				ansm=tot;
				ansk=k;
			}
		}
	}
	printf("%d %d",ansk,ansm);
}

```

蒟蒻写题解不易，如果对你有帮助，点个赞呗

---

## 作者：pikabi (赞：17)

### ~~**为了缓解一下我军训归来的疲惫身心， 我决定以发题解来愉悦身心**~~


------------

好吧进入正题————>>
  
------------
原题的翻译：N头牛排成一列1<=N<=5000。每头牛或者向前或者向后。为了让所有牛都 面向前方，农夫每次可以将K头连续的牛转向1<=K<=N，求操作的**最少次数M和对应的最小K**。

这里需要注意了， 翻译先说M后说K，这很容易误导大家，而且样例的结果3 3也不明显。输出格式如图(ﾉﾟ▽ﾟ)ﾉ

![](https://img-blog.csdnimg.cn/20190826110539491.png)

###              先K再M！！
这可能是大家爆20分的原因QAQ.

------------

题目分析————>>

n头牛，B表示朝后（back）， F表示朝前（front），这是很明显的**贪心**。要求把n头牛都朝前。因为可以将连续的k头牛翻转，我们不妨**令朝前为1， 朝后为0，目的是把所有0变1。翻转规则是0变1，1变0。** 翻转时， 我们不妨以第i头牛为起点，**如果它朝后，就把它及后面的连续k头牛翻转；反之则不转**。再考虑第i+1头牛。为什么呐？因为这么做以后，之后的翻转对这些曾作为起点的牛已经没有影响了，而我们已经把这些牛都朝前，所以只需要考虑后面没有做过起点的牛是不是朝前，若全朝前，则更新答案了QAQ。

每头牛做起点要么转要么不转,因为转2次和不转没什么区别我想大家都应该知道吧QAQ

### **~~然而这样暴力只能拿到80分~~**

## 80分 Code

```cpp
// luogu-judger-enable-o2
#include <cstdio>

using namespace std;

int n, a[5005][5005], minn = 99999, step , pin;

int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		char ch;
        getchar();
		ch = getchar();
		if(ch == 'B') a[0][i] = 0;
		else a[0][i] = 1;
	}
	for(int i = 1; i <= n; i++){
		step = 0;
		int flag = 0;
		for(int j = 1; j <= n; j++)
		a[i][j] = a[0][j];
		for(int j = 1; j <= n - i + 1; j++){
			if(!a[i][j]){
			for(int k = 0; k < i ; k++){
				a[i][j + k] ^= 1;
			}
			step++;
			if(step > minn) break;
			}
		}
		for(int j = n - i + 2; j <= n; j++){
			if(!a[i][j]){
				flag = 1;
				break;
			}
		}
		for(int j = 1; j <= n; j++)
		if(!flag) {
			if(minn > step)
			{
				minn = step;
				pin = i;
			}
		}
	}
	printf("%d %d", pin, minn);
	return 0;
} 
```
这样子就有**好多好多（!!!∑(ﾟДﾟノ)ノ）个n^2**了！！！

那肿么办呢？
这时候， 就要用到一个我也讲不清楚名称的一个方法(感jio是差分？？？)/手动滑稽
————>>

------------
先来学习一下‘ ^ ’的基本知识

‘ ^ ’名曰异或， ~~英文为exclusive OR，缩写成xor，其运算法则为：a⊕b = (¬a ∧ b) ∨ (a ∧¬b)~~，0 ^ 1 为1， 1 ^ 0 为1, 0 ^ 0为0 , 1 ^ 1为0。简而言之，**同为0，异为1**。

那么 ‘ ^ ’到底有虾米用呢？大家想想看，先把now设为0，由上述规则易得， 1和0 ^ 0都等于它本身， 而 ^ 1都等于非1和非0。所以如果将牛给转向了， 我们就将**now ^= 1**, 即将now非一下，然后将每头牛都 **^= now**, 就能知道这头牛目前的状态。但是第i+k头牛及之后都是不转的，所以我们又用一个数组b来储存，b初值设为0，将**b[i+k] ^= 1**。 每次都将**now ^= b[i]**, 就可以将now调整过来。具体~~不严谨的~~证明：~~根据百度百科等运算规律及大脑想象~~分析得————>> 因为b[i] ^= 1 , now ^= 1,所以 now ^= b[i] = now。朴素的想法是:**由于now和b的初值都是0，所以将now非一下变成1， b非一下变成1， 1^1还是0，就相当于不转了，多个重叠在一起也一样**。
这一片段代码如下↓↓↓

```cpp
for(int i = 1; i <= n; i++){
	memset(b,0,sizeof(b));//归零
	now = 0;
	step = 0;//步数
	int flag = 0;
	for(int j = 1; j <= n; j++)//传递
	dif[j] = a[j];
	for(int j = 1; j <= n - i + 1; j++){//要注意范围
		now ^= b[j];//调整now
		dif[j] ^= now;//调整牛的朝向
		if(!dif[j]){//转向，此时dif[i]不修改也无所谓，对后面不影响
			now ^= 1;
			b[i + j] ^= 1;
			step++;
		}
	}
	for(int j = n - i + 2; j <= n; j++){//查看后面是否都朝前
		now ^= b[j];
		if(!(dif[j] ^ now)){
			flag = 1;
			break;
		}
	}
	if(!flag) {//如果都朝前
		if(minn > step)
		{
			minn = step;
			pin = i;//我们管pin叫针|ू･ω･` )
		}
	}
}
```
------------
~~151ms让我傲娇一下૮(ﾟ∀ﾟ)ა~~

------------


## 完整代码

```cpp
// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>

using namespace std;

int n, a[5005], minn = 99999, step , pin, dif[5005], now, b[5005];

int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){//这是读入QAQ
		char ch;
        getchar();
		ch = getchar();
		if(ch == 'B') a[i] = 0;
		else a[i] = 1;
	}
	for(int i = 1; i <= n; i++){//同上
		memset(b,0,sizeof(b));
		now = 0;
		step = 0;
		int flag = 0;
		for(int j = 1; j <= n; j++)
		dif[j] = a[j];
		for(int j = 1; j <= n - i + 1; j++){
			now ^= b[j];
			dif[j] ^= now;
			if(!dif[j]){
				now ^= 1;
				b[i + j] ^= 1;
				step++;
			}
		}
		for(int j = n - i + 2; j <= n; j++){
			now ^= b[j];
			if(!(dif[j] ^ now)){
				flag = 1;
				break;
			}
		}
		if(!flag) {
			if(minn > step)
			{
				minn = step;
				pin = i;
			}
		}
	}
	printf("%d %d", pin, minn);
	return 0;
} 
```


------------
如果叙述不当或者不懂可以评论喔QAQ

完结撒花**╰( ´・ω・)つ──☆✿✿✿**


---

## 作者：LevenKoko (赞：11)

### 有问题可以私信问我，评论很少看...因为没有提醒

#### 这是一篇半娱乐性题解

## 但也是一个只要会暴力就能A的题解

主要介绍一些卡常优化+一些**NOIP并不能用**的优化，关于正解的预处理或是贪心这里不做介绍

显然正解要考虑贪心或者对每个点进行翻转预处理（O(2*N^2)），但这里是一篇**暴力+毒瘤优化**过的题解...

~~无聊想刷水题然而却T了...怒怼一波常数~~

首先基本的读优+输优（优化1，并没有什么用，还是会T）

从大到小枚举区间长度，找到正解直接退出（优化2）

区间复制的时候memcpy（优化3）

循环变量的register 和++i（优化4）

好吧，其实上面的优化都是只起到一点点作用的...

优化5：Luogu自带O2

优化6：手动O3等等，可以优化到500ms左右

```
// luogu-judger-enable-o2
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
const int M=1e9+7;
using namespace std;
inline int read(){
    char chr=getchar();	int f=1,ans=0;
    while(!isdigit(chr)) {if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr))  {ans=(ans<<3)+(ans<<1);ans+=chr-'0';chr=getchar();}
    return ans*f;
}
void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;char a[5005],b[5005];
inline void rever(char &x){
    if(x=='B') x='F';
    else x='B';
}
signed main(){
    n=read();
    for(int i=1;i<=n;++i)a[i]=getchar(),getchar();
    for(int k=n;k>=1;--k){
        memcpy(b,a,sizeof b);
        int t=0;
        for(register int i=1;i+k-1<=n;++i){
            if(b[i]=='B'){
                ++t;
                for(register int j=i;j<=i+k-1;++j) rever(b[j]);
            }
        }
        int ff=0;
        for(int i=1;i<=n;i++) if(b[i]=='B') ff=1;
        if(ff) continue;
        cout<<k<<" "<<t<<endl;
        return 0;
    }
    return 0;
}

```

---

## 作者：MrMorning (赞：10)

这道题没有一个比较详细的题解，我来提供一份。

首先我们可以知道，反转区间的顺序对结果没有影响，而且一个区间如果翻转两次以上是没有意义的，所以，问题就变成了求哪些区间需要反转。

我们枚举k。对于每一个k，我们设计一个calc函数来判断k的操作次数。

显然的，我们可以设计出一种方法，就是每一次都检查最左端，然后进行反转，很容易写出下面的calc函数。

```cpp
int calc(int k) {
    int ans = 0;
    int i; 
    for(i = 1; i + k - 1 <= N; i++) {
        if(f[i] == 1) {
            for(int j = i; j <= i + k - 1; j++) {
                f[j] = !f[j];
            }
            ans++;
        }
    }
    for(i--; i <= N; i++) {
        if(f[i] == 1) return -1;
    }
    return ans;
}
```
这样的检查方式复杂度为O(n2)，再结合枚举k，总的复杂度是O(n3)，这样的复杂度可以通过70%的数据，但还不够好。

我们来考虑怎么优化。显然的，我们没有必要去记录每一个的状态，我们只需要存储每一个区间是否反转过。所以，我们定义

f[i]为区间[i, i+k-1]是否反转。

这样，反转的复杂度就降到了O(1)，总的复杂度就降到了O(n2)，这样我们就可以AC这道题了。

对于实现上还有一个问题，就是怎么判断每一个格子的状态，这个问题我们留给读者思考。

下面贴上calc的代码。

```cpp
int calc(int K) {
    memset(f, 0, sizeof(f));
    int ans = 0;
    int sum = 0;
    for(int i = 0; i + K <= N; i++) {
        if((g[i] + sum) % 2 != 0) {
            ans++;
            f[i] = 1;
        }
        sum += f[i];
        if(i - K + 1 >= 0) sum-=f[i-K+1];
    }
    for(int i = N - K + 1; i < N; i++) {
        if((g[i] + sum) % 2 != 0) {
            return -1;
        }
        if(i-K+1 >= 0) {
            sum-=f[i-K+1];
        }
    }
    return ans;
}
```
如果有问题，可以私信。


---

## 作者：Su_Zipei (赞：4)

## 分析
这个题来看的话好像有点难下手，不如再去读一遍题 ~~N遍~~，发现一句话很重要**Each time the machine is used, it reverses the facing direction of a contiguous group of K cows in the line**，就是说只能翻转固定的长度区间，那这样是不是就可以枚举区间了？枚举一层区间,再枚举每次起点，最后加上区间修改，时间复杂度$O(N^3)$，肯定会T掉，接下来就考虑优化了。

优化怎么入手呢？时间主要就是出在这三层循环上，只要省掉一层循环，时间复杂度就能到$O(N^2)$，这样就可以过，第一层循环，显然不能省略，第二层同样，只有在区间修改这一层循环上可以做点手脚，回忆区间修改，有几种做法，线段树，树状数组，还有差分，前两者用在这都有点大材小用或是说不是很合适，因为判断是否区间修改完成不好判断，而差分用在这个区间上就很合适了。那我们大概思路也就有了，首先读入数组，将B标记成1，F标记成0，这里怎么标记都无所谓，然后利用枚举区间，差分修改，最后输出答案，下面考虑一下细节。

我们枚举区间完，要从左到右一次反转区间，为什么呢？题目中要求的是最小次数，就是要先保证次数最小，再考虑区间长度，而我们如果先修改后面的，把后面改好了，再去改前边的，结果一定不会比先改前边的好（**有可能相等，如00100**），所以我们为保证最小次数，一定从最左端开始依次枚举，如果这个点不符合，就把他后面的整个区间翻转，这里就要用到差分了，肯定直接修改会T掉，我们可以考虑，如果这个区间要修改，那么原来的1会变成2，0会变成1，好像没什么规律，但再看就发现所有的奇数都需要改变，偶数就不用，每次修改给整个区间加一，判断奇偶数就行，然后这就变成了一个区间加一个数的操作，相信大家应该都会。这样修改就完成了，那么怎么判断能不能完成题目的任务呢？

由题意可以知道如果当前区间长度小于修改的区间长度，是不能修改的，也就是从n往前的长度为len的区间总是无法被修改的，所以判断这一段区间内有无不满足条件的点即可。

最后找答案的时候也有一个地方，就是当操作修改次数不同时，直接用操作修改次数最小的那个答案就行，但如果当前操作次数和原来答案相同，是不是要考虑一下区间长度改成最小值？答案显然是**不是**，…………，因为我们是从小到大枚举的区间长度，所以在遇到相等的时候，已经得到的答案的区间长一定是小的，所以只在次数不同时修改答案，但判断上也不会错。
## 其他优化
当然以下优化不加也没问题，毕竟算法时间复杂度足够过掉这道题。
我做完之后看了看时间大概700ms左右，好像有点高，看别人的时间好像没有特别大，所以我加了加小优化。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ezh4z50.png?x-oss-process=image/resize,m_lfit,h_00,w_500)

为方便说，由上到下一次标号$1-4$,1,2跑的时间还是挺快的但对$NOIp$没啥用，$NOIp$不可能给你开O2也不可能给你c++17，所以还是看一下3和4，这俩时间大概有一倍的关系，看一下代码吧
# 3
```
#include<cstdio>
#include<cstring>
using namespace std;
const int N=5e3+10;
char s[3];
int cf[N],a[N];
int min(int a,int b){
    if(a<b)return a;
    else return b;
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        if(s[0]=='B')a[i]=1;
        else a[i]=0;
    }
    int res=0x3f3f3f3f,ans=0x3f3f3f3f;
    for(int len=1;len<=n;len++){
        int cnt=1,k=0;memset(cf,0,sizeof(cf));
        for(int i=1;i<=n;i++){
            cf[i]+=cf[i-1];
            if(i+len-1<=n){
                if(a[i]+cf[i]&1){
                    cf[i]++;cf[i+len]--;k++;
                }
            }else if(cf[i]+a[i]&1){cnt=0;break;}
        }
        if(cnt)
            if(k<ans){
                ans=k;res=len;
            }
            else if(k==ans)res=min(res,len);
    }
    printf("%d %d",res,ans);
    return 0;
}

```
## 4
```
#include<cstdio>
#include<cstring>
using namespace std;
const int N=5e3+10;
char s[3];
int cf[N],a[N];
int min(int a,int b){
    if(a<b)return a;
    else return b;
}
int main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        if(s[0]=='B')a[i]=1;
        else a[i]=0;
    }
    int res=0x3f3f3f3f,ans=0x3f3f3f3f;
    for(int len=1;len<=n;len++){
        int cnt=1,k=0;memset(cf,0,sizeof(cf));
        for(int i=1;i<=n;i++){
            cf[i]+=cf[i-1];
            if(i+len-1<=n){
                if(a[i]+cf[i]&1){
                    cf[i]++;cf[i+len]--;k++;
                }
            }else if(cf[i]+a[i]&1)cnt=0;
        }
        if(cnt)
            if(k<ans){
                ans=k;res=len;
            }
            else if(k==ans)res=min(res,len);
    }
    printf("%d %d",res,ans);
    return 0;
}

```
其实就是少一个break，感觉这个加上还是很有必要的，因为可能极限数据的时候，CCF那评测机状态不好，再卡一下，可能会出问题。
## 问题
那么有没有可能最开始全部是朝前的呢？答案是没有，英文题面中已经讲到，**有一些**牛，所以说不可能其实全部朝前边的。

---

## 作者：hzoi_liuchang (赞：4)

[链接](https://www.cnblogs.com/liuchanglc/p/12643679.html)
## 分析
题目中给出了两种字母B和F，很显然，用字符数组写代码很不方便，所以我们将B转化为0，F转化为1

那么这道题就变成了将一个只含有0和1的数组进行多次取反，使得最终数组里的元素全都变成1
```cpp
for(int i=1;i<=n;i++){
          scanf(" %c",&s);
          if(s=='B') a[i]=0;
          else a[i]=1;
      }
```
这道题暴力还是比较好想的，我们可以将每次操作反转的长度k从1到n开始枚举

对于每一个k值，我们从1到n枚举长度为k的区间

因为同一个点翻转两次就与没有翻转的效果相同了，因此我们有一个贪心策略为：

从左到右对于出现的每一个B翻转一次

从当前点开始的区间，就能保证是最优解。

如果f[i]=0，那么把f[i]到f[i+k-1]这个长度为k的区间中的元素全部取反

取反后继续从i+1遍历，重复上一步

这样，从1到n的每一个值，我们都需要把它进行一次遍历

时间复杂度为n^3
```cpp
int solve(int k) {
    int ans = 0;
    int i; 
    for(i = 1; i + k - 1 <= N; i++) {
        if(f[i] == 1) {
            for(int j = i; j <= i + k - 1; j++) {
                f[j] = !f[j];
            }
            ans++;
        }
    }
    for(i--; i <= N; i++) {
        if(f[i] == 1) return -1;
    }
    return ans;
}
```
很显然n=5000的数据过不了，不过还是可以拿一部分分的

## 优化
n^3的复杂度过不了，我们可以考虑省去一重循环，把它变成n^2

第一层是枚举区间k的大小，这一层我们显然不能省去，枚举每一个元素也不能省去

而且它们也不具有单调性，因此二分也不可以

那么我们再重新考虑一下操作的性质

对于一个数，如果对它操作偶数次，那么相当于没有操作

如果对它操作奇数次，那么相当于取反一次

所以我们没有必要去记录每一个的状态，我们只需要存储每一个元素被反转的次数

那么我们就可以用差分数组（名称为cf）记录该元素被操作的次数

如果该元素是1，那么它被操作偶数次才符合要求，如果是0就要操作奇数次

所以如果当前元素不符合要求，那我们就更新操作数,把cf[i]++,同时要把f[i+k-1]--，因为该操作只对[i,i-k+1]这个区间有效
```cpp
 if((a[i]+cf[i])%2==0){
     cf[i]++;
     cf[i+k]--;
     js++;
 }
```
维护代码如上

那么什么情况下不成立呢？

很简单，当序列后面的元素数目不足k-1个的时候,判定这个k不成立直接跳过去

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=5010;
char s;
int a[maxn],cf[maxn];//cf差分数组,a原始数组
int n;
int solve(int k){
    int js=0;//记录区间取反的个数
    memset(cf,0,sizeof(cf));//不要忘了初始化
    for(int i=1;i<=n;i++){
        cf[i]+=cf[i-1];//维护差分数组
        if(i+k-1<=n){
            if((a[i]+cf[i])%2==0){
                cf[i]++;
                cf[i+k]--;
                js++;
            }//如果这个节点仍然是0，操作数加一
        }else{
            if((a[i]+cf[i])%2==0){
                return 0x3f3f3f3f;
            }//上面讲的不成立的情况
        }
    }
    return js;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf(" %c",&s);
        if(s=='B') a[i]=0;
        else a[i]=1;
    }
    int cd=1,cx=n;//cx记录最小反转次数,cd记录操作的区间长度
    for(int i=1;i<=n;i++){
        int ans=solve(i);
        if(ans!=0x3f3f3f3f && ans<cx){
            cd=i;
            cx=ans;//如果成立，更新
        }
    }
    printf("%d %d\n",cd,cx);
    return 0;
}
```


---

## 作者：feng_chengjie (赞：4)

##其实是一个非常巧妙的顺序模拟

基本思路同楼下，但是在检验k时还可以写得更加清晰：

记f[i]为i这个点是多少个操作的终止节点，记t为当前此点受到的影响数（奇数次改变方向，偶数次不变），记st为已经操作多少次。

每当判断到$(a[i]+t)%2==1$时(我把F记为0，B记为1)，就必须进行操作，标记它的终止标记

每当判断到$f[i]>1$时，说明有$f[i]$个操作终止了，则$t-=f[i]$，并将$f[i]$清零

最后判断$n-k+2~n$有没有还没反过来的，无则尝试更新答案，有则放弃该次的$k$


参考代码：



```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,g[5005],f[5005];
char c;
int ans=0,kk;
int main()
{
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>c;
        if(c=='F') g[i]=0;
        else g[i]=1;    
    }
    ans=1e9;
    for(int k=1;k<=n;k++)
    {
        memset(f,0,sizeof(f));
        int t=0,ok=1,st=0;
        for(int i=1;i+k-1<=n;i++)
        {
            if((g[i]+t)%2==1)
            {
                f[i+k-1]++;    
                t++;
                st++;
            }    
            if(f[i])
            {
                t-=f[i];
                f[i]=0;    
            }
        }
        for(int i=n-k+2;i<=n;i++)
        {
            if((g[i]+t)%2==1)
                ok=0;    
            if(f[i])
            {
                t-=f[i];
                f[i]=0;    
            }
        }
        if(ok && st<ans)
        {
            ans=st;
            kk=k;    
        }
    }
    cout<<kk<<" "<<ans;
    return 0;
} 

```

---

## 作者：王钰翔 (赞：3)

# 暴力=（前缀和+差分+枚举）
## 思路很简单：如果有牛反着，将它以及它后面的牛翻转。（这种做法必然最优）
### **不多说了，直接上代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char ch;
bool cow[5005]; //牛的原本状态
int f[5005]; // 前缀+差分
int minn=5005,k; //
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>ch;
		if(ch=='F') {
			cow[i]=1; // 将字母转换为数字状态 ‘0 ’为 ‘B ’ ，‘1 ’为 ‘F ’
		}
	}
	for(int i=1; i<=n; i++) { // 枚举转动牛个数
		memset(f,0,sizeof(f)); //  清空状态
		int ans=0;
		for(int j=1; j<=n; j++) { // 这里一定不能写 j<n (要把所有的牛全部举例一遍)
			if(abs((cow[j]+f[j-1]+f[j]))%2==0&&j+i-1<=n) { // -1%2==-1 注意 连续的翻转不可以翻空气
				f[j]+=f[j-1]+1; //
				f[j+i]-=1;    // 这两句是关键 差分+前缀和
				ans++;
			} else if(abs((cow[j]+f[j-1]+f[j]))%2==1) {
				f[j]+=f[j-1]; //不翻转也要前缀和
			} else { // 相当于 else if(abs((cow[j]+f[j-1]+f[j]))%2==0&&j+i-1>n)
				ans=99999;  // 防止读入答案
			}
		}
		if(minn>=ans) {
			if(minn==ans) {
				minn=ans;
			} else { // K要取最小值
				minn=ans;
				k=i;
			}
		}
	}
	cout<<k<<" "<<minn;
    return 0;
}
```


---

## 作者：万弘 (赞：2)

首先可以发现对于给出k的情况，可以在至多$O(n^2)$的时间内求出至少需要几步（或不可能全部朝前）

这里可以想到二分答案，然后检验。可惜这一题不满足单调性，于是我们只能枚举每个k。但这样的复杂度是$O(n^3)$,跑不动5000.

考虑优化检验部分。在$O(n^2)$的暴力检验中，每次改变牛$i$的方向需要把它和它后面$k-1$头牛的方向，这样是最坏$O(n^2)$.

考虑差分，即每次只修改$i,i+k-1$,然后通过前缀和求解每一位是否反转。由于反转奇数次使方向相反，偶数次使方向不变，所以可以使用异或。最后的总复杂度是$O(n^2)$

代码：
```cpp
//Wan Hong 2.2
//home
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long ll;
typedef std::string str;
#define INF (1ll<<58)
ll read()
{
	char c;
	ll f=1,x=0;
	do
	{
		c=getchar();
		if(c=='-')f=-1;
	}while(c<'0'||c>'9');
	do
	{
		x=x*10+c-'0';
		c=getchar();
	}while(c>='0'&&c<='9');
	return f*x;
}
ll max(ll a,ll b)
{
	return a>b?a:b;
}
ll min(ll a,ll b)
{
    return a<b?a:b;
}

/**********/
#define MAXN 5011
ll a[MAXN],c[MAXN],n;
ll check(ll k)//检验k，返回最少步数（INF表示不可能全朝前）
{
	memset(c,0,sizeof c);
	ll sum=0,res=0;
	for(ll i=1;i<=n-k+1;++i)
	{
		ll x=sum^a[i];
		if(x)
		{
			++res;
			c[i]^=1;c[i+k-1]^=1;
		}
		sum^=c[i];
	}
	for(ll i=n-k+2;i<=n;++i)
	{
		ll x=sum^a[i];
		if(x)return INF;
		sum^=c[i];
	}
	return res;
}
int main()
{
	n=read();
	for(ll i=1;i<=n;++i)
	{
		char c=getchar();
		while(c!='B'&&c!='F')c=getchar();
		a[i]=(c=='B');
	}
	ll t,ans=INF;
	for(ll k=1;k<=n;++k)
	{
		ll p=check(k);
		if(p<ans)
		{
			t=k;ans=p;
		}
	}
	printf("%lld %lld",t,ans);
	return 0;
}
```

---

## 作者：DarthVictor (赞：1)

## 题目
[原题链接](https://www.luogu.com.cn/problem/P2882)
## 解说
题目大致就是说，有n头奶牛排成一队，有的脸朝前有的脸朝后，F代表前，B代表后。现在有一种操作可以让连续K头奶牛同时反转，问至少要反转多少次，此时K至少为多少。先输出K，再输出最小反转次数。

显然我们需要从1到n挨个尝试K的可能取值，并从中选取最优，主要问题在于怎么算K一定时的最小反转次数呢？自然想到遍历区间。从[1,k]区间遍历到[n-k+1,n]，对于每一个区间，如果区间的第一个是反的，那么我们就把整个区间反转。当然我们不可能直接修改原数组因为后面还要用，那么我们就用一个sum标记前k-1修改了多少次来确定当前是否需要修改。

（部分解释放在了代码里）
## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm> 
using namespace std;
const int maxn=5000+3;
int a[maxn],n,flag[maxn];
int solve(int k){
    int i;
    memset(flag,0,sizeof(flag));
    //flag[i]表示区间[i,i+k-1] 是否需要翻转
    int sum=0,cnt=0;//前k-1个转变的次数
    for(i=1;i<=n-k+1;i++){
    //sum记录走到当前i，其前面k-1个翻转了多少次
        if(i-k>=1){
            sum-=flag[i-k];
        }
        if(a[i]==0&&sum%2==0){
        //如果是B 且前面翻转了偶数次 仍旧需要翻转
             flag[i]=1;
             sum+=flag[i];
             cnt++;
        }
        else if(a[i]==1&&sum%2==1){
        //如果是F  且前面翻转了奇数次
            flag[i]=1;
            sum+=flag[i];
            cnt++;
        }
    }
    for(i;i<=n;i++){
        if(i-k>=1)
        {
            sum-=flag[i-k];
        }
        if(sum%2==0&&a[i]==0) return -1;
        else if(sum%2==1&&a[i]==1) return -1;
    }
    return cnt;
}
int main(){
    int k=1,Max;
    char s[1];
    scanf("%d",&n);
    Max=100010000;
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        if(s[0]=='B') a[i]=0;
        else if(s[0]=='F') a[i]=1;
    }
    for(int i=1;i<=n;i++){
        int mid=solve(i);
        if(mid==-1) continue;
        if(Max>mid){
            Max=mid;
            k=i;
        }
    }
    printf("%d %d",k,Max);
    return 0;
}
```
幸甚至哉，歌以咏志。

---

## 作者：Erina (赞：1)

这是一种在USACO里面十分常见的提醒.

之前已经见过三四次了.

那么这一题的操作有什么不同点呢?

我们仔细观察一下, 同一个地方反转两次就是zz操作了对吧......

那么竟然每一个地方只需要翻一次, 那么我们就考虑从左往右翻.

那么如果一开始那头牛是向后的, 那么就翻最左面的区间, 之后就不再动它.

然后同理看第二头牛......

然后我们就可以从小到大枚举反转长度, 然后就可以顺利的AC了.

这种每个位置只操作一次的题型在USACO中是十分常见的, 思路就是按一种比较简单的顺序去操作.

比如说这道题的二维版本, 一次反转的是它和它周围4个格子的值, 我们是枚举第一行, 然后就再也不翻转第一行了. 然后我们就一直向下操作.

还有另一个一定是$4*4$的二维版本, 就是每一次会反转全行以及全列.发现每一次我们操作时反转全行全列一定不会出锅, 我们就这么做. 然后去除重复的就好了.

放一下这题的代码......

```cpp
#include<iostream>
#include<cstring>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[1000000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
#define peek() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s)
	inline int read() {
		int x = 0;
		char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using namespace fio;
int n, arr[100005];
int brr[100005], cf[100005];
int chk(int x) {
	memset(cf, 0, sizeof(cf)), memcpy(brr, arr, sizeof(brr));
	int ans = 0;
	for (int i = 1; i <= n - x + 1; i++) {
		brr[i] ^= cf[i] ^= cf[i - 1];
		if (brr[i])ans++, cf[i] ^= 1, cf[i + x] ^= 1;
	}
	for (int i = n - x + 2; i <= n; i++) { brr[i] ^= cf[i] ^= cf[i - 1]; if (brr[i])return -1; }
	return ans;
}
int minn = 0x7fffffff, ans;
int main() {
	n = read();
	for (int i = 1; i <= n; i++) { while (!isupper(peek()))gc(); arr[i] = (gc()) == 'B'; }
	for (int i = 1; i <= n; i++) {
		int x = chk(i);
		if (x != -1 && x < minn)minn = x, ans = i;
	}
	cout << ans << ' ' << minn;
}
```


---

## 作者：Jerrycyx (赞：0)

首先，**翻转的顺序不影响最终结果**，所以我们可以规定它从左往右顺序翻转。

其次，假设某个位置 $x$ 以前的所有牛都已经处理为 `F`，那么当 $x$ 位置出现 `B` 时：

+ 在顺序翻转下，如果从左边某头牛 $y$ 开始翻转来影响它，那么要使 $y$ 回到 `F`，要么在原位翻一遍（等于啥也没干），要么用更左边某头牛 $z$ 来影响 $y$（把 $y$ 看成 $x$，$z$ 看成 $y$，相当于又回到了这个问题上，无法以合法情况结束；同时还不符合“顺序翻转”的规定）。

+ 而如果在它右侧翻转根本不影响 $x$，更不行了。

综上所述，**必须恰好从 $x$ 开始翻转一次来使它变成 `F`**。

解法也就有了：枚举 $k$，通过这种方式来翻转序列。如果处理完以后还有 `B`，代表这个 $k$ 不合法；否则用得到的 $m$ 来更新答案。

但是暴力翻转序列所需总时间复杂度为 $O(n^3)$，过不了这道题（$70$ Pts）。虽然据说卡常能卡过，但我们需要更加优雅的方法。其他大佬普遍用差分，但是我这里使用的是**队列**。

+ 开一个队列，记录开始翻转的位置。
+ 每到达一个新的点 $i$，就将队尾已经无法覆盖 $i$ 的翻转起始点弹出，保证队列中所有起始点都是能覆盖 $i$ 的。
+ 此时队列的大小就是 $i$ 被覆盖的次数，根据其奇偶性来反转 $i$ 即可。如果反转完依然是 `B`，则将 $i$ 入队，并将其调正。

最后判断处理完毕后的序列是否合法即可。

-----

代码上，`B` 和 `F` 可以分别处理成 `true` 和 `false` 存入一个 `bitset` 当中。

使用 `bitset` 不仅可以直接使用 `=` 进行复制以进行临时计算，也可以用 `any()` 方便地对判断序列是否合法，还能节省一些常数。

时间复杂度 $O(N^2)$。

代码如下：

```cpp
#include<cstdio>
#include<bitset>
#include<queue>
using namespace std;

const int N=5005;
int n,ansk,ansm=0x3f3f3f3f;
bitset<N> a,t;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		char ch[5]; scanf("%s",ch);
		a[i]=(ch[0]=='B');
	}
	for(int k=1;k<=n;k++)
	{
		int m=0; t=a;
		queue<int> q;
		for(int i=1;i<=n;i++)
		{
			while(!q.empty() && q.front()<i-k+1) q.pop();
			if(q.size()&1) t.flip(i);
			if(i+k-1<=n && t[i])
			{
				q.push(i);
				t.flip(i);
				m++;
			}
		}
		if(!t.any() && m<ansm)
			ansk=k,ansm=m;
	}
	printf("%d %d\n",ansk,ansm);
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/198912840)

---

