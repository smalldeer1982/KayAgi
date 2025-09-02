# 「RdOI R3」毒水

## 题目描述

**这是一道 IO 交互题。**

现在你面前有 $n$ 瓶水，从 $1\sim n$ 编号，其中有 $1$ 瓶水有毒，你可以用一些小白鼠来进行判断。

但是你找的小白鼠中**有且仅有**一只**变异鼠**，**如果它喝的水中有毒水，那么它不会死亡。否则它会在 $59$ 秒内死亡。其它小白鼠如果喝了毒水将在 $59$ 秒内死亡，否则不会死亡**。

你需要在一分钟内找出这瓶毒水，因为测试已经花了 $59$ 秒，所以你的代码只能运行 $1$ 秒。

### 交互方式

首先你需要从标准输入读取两个整数 $n$，$maxk$，表示水的数量，以及你最多能找到的小白鼠个数。

若你需要 $k$ 只小白鼠，你需要向标准输出打印 $k+1$ 行，除了最后一行，每一行的格式为：`1 m B1 B2 ... Bm`，表示你找到一只小白鼠并让它喝 $B_1$ 号，$B_2$ 号，$\cdots$，$B_m$ 号这 $m$ 瓶中的水。你需要在最后写上一行：`2`，随后清空缓冲区，表示你不需要更多的小白鼠了。

下面是一些语言的刷新缓冲区操作：

- C++：`fflush(stdout)` 或 `cout.flush()`。
- C: `fflush(stdout)`。
- Java: `System.out.flush()`。
- Python: `stdout.flush()`。
- Pascal: `flush(output)`。
- 其他语言：请参考对应语言的帮助文档。

当然，如果 $k>maxk$，交互库会返回 `WA`、`RE`、`UKE` 或 `TLE`，同时该测试点不得分。

然后你需要从标准输入读取 $k$ 个整数 $R_1,R_2,\cdots,R_k;R_i\in\{0,1\}$。若 $R_i=0$ 代表第 $i$ 号小白鼠已死亡，否则代表第 $i$ 号小白鼠仍存活。

最后你需要从标准输出打印一个整数，表示毒水的编号。

## 说明/提示

### 样例说明

毒水的编号为 $2$，且第 $2$ 次和第 $10$ 次均为让小白鼠喝下 $2$ 号毒水，故这两次操作返回的结果为 $0$。其他操作由于让小白鼠喝的不是毒水，返回的结果为 $1$。

**样例仅为理解交互方式使用，可能不符合逻辑。**

---

### 数据范围

**本题采用捆绑测试。**  

**注意：本题不存在一个 subtask 包含其他所有 subtask**。

| subtask | 分值 | $n$             | $maxk\ge$ |
| ------- | ---- | --------------- | ------- |
| $1$     | $1$  | $=1$            | $0$     |
| $2$     | $9$  | $\le 1000$      | $3000$  |
| $3$     | $20$ | $\le 1000$      | $30$    |
| $4$     | $30$ | $8\le n \le 16$ | $7$     |
| $5$     | $40$ | $\le 1000$      | $15$    |

---

### 注意

只有你向交互器发送 $2$ 操作时，交互器才会将你先前的 $1$ 操作的答案告诉你。也就是说，你不能在执行一次 $1$ 操作后立刻得到这次操作的返回结果。

## 样例 #1

### 输入

```
4 12













1 0 1 1 1 1 1 1 1 0 1 1
```

### 输出

```

1 1 1
1 1 2
1 1 3
1 1 4
1 1 1
1 1 2
1 1 3
1 1 4
1 1 1
1 1 2
1 1 3
1 1 4
2

2```

# 题解

## 作者：abruce (赞：30)

由于出题人咕了，所以由我验题人来写一篇（备用）题解。  
很妙的题。  
### 10pts  
对于每瓶水，我们用 $3$ 只小白鼠来检验，如果有一瓶水有超过两只小白鼠死亡，则这是毒水。最大需要 $3000$ 只。  
### 30pts  
如果没有变异鼠，这是一个非常经典的问题，我们可以考虑二进制分组，对于第 $i$ 只小白鼠，我们让它喝下二进制下第 $i$ 位为 $1$ 的所有水，这样就可以通过二进制拼出来哪瓶是毒水。  
但是因为变异鼠的存在，所以我们对于每个二进制位都需要 $3$ 只小白鼠来检验。最大需要 $30$ 只。  
## 100pts  
我们发现对于每个二进制位都用 $3$ 只小白鼠来检验太浪费了，我们来考虑怎么优化。  
我们可以再重复一次上面的过程。首先肯定是要用 $10$ 只小白鼠每个二进制位用一只。然后我们再对这 $10$ 只进行二进制分组。新用 $4$ 只小白鼠，第 $i$ 只小白鼠代表这 $10$ 只中二进制位为 $1$ 的小白鼠所喝的水的异或。最后还需要 $1$ 只小白鼠喝前面这 $4$ 只小白鼠所喝的水的异或。一共需要 $15$ 只，刚好满足。  
如果选的最后 $5$ 只鼠中有奇数只被毒死，这说明中间有变异鼠，因为这 $5$ 只鼠总共把每瓶水都喝了偶数次。那么前面 $10$ 只就都是有效信息，用它们判断即可。  
否则说明变异鼠在前面 $10$ 只中，这时我们就要用中间那 $4$ 只进行检验。如果它和它所管辖的小白鼠状态异或起来得到 $1$，那么就说明它管辖的小白鼠中有变异鼠。  
这样我们就可以得知变异鼠的位置，把它的状态改变即可。  
下面是代码。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,v[16],cnt;
bitset<1005> b[16],bit;
bool pd;
int main() {
	int x,lg,lglg;
	cin>>n>>k,bit.set();
	if(n==1)return cout<<2<<endl<<1<<endl,0;
	if(n==2) {
		cout<<"1 1 1"<<endl<<2<<endl;
		cin>>x;
		cout<<2-x<<endl;
		return 0;
	}
	lg=log2(n-1)+1;
	lglg=log2(lg-1)+1;
	for(register int i=0; i<lg; i++) {
		int cnt=0;
		for(register int j=0; j<n; j++)if(j&(1<<i))cnt++,b[i][j]=1;
		cout<<"1 "<<cnt<<' ';
		for(register int j=0; j<n; j++)if(j&(1<<i))cout<<j+1<<' ';
		cout<<endl;
	}
	for(register int i=0; i<lglg; i++) {
		cout<<"1 ";
		for(register int j=0; j<lg; j++)if(j&(1<<i))b[i+lg]^=b[j];
		cout<<b[i+lg].count()<<' ';
		for(register int j=0; j<n; j++)if(b[i+lg][j])cout<<j+1<<' ';
		cout<<endl;
		b[lg+lglg]^=b[i+lg];
	}
	cout<<"1 "<<b[lg+lglg].count()<<' ';
	for(register int j=0; j<n; j++)if(b[lg+lglg][j])cout<<j+1<<' ';
	cout<<endl<<2<<endl;
	for(register int i=0; i<=lg+lglg; i++)cin>>v[i],v[i]^=1;
	for(register int i=lg; i<=lg+lglg; i++)pd^=v[i];
	if(!pd) {
		int fake=0;
		for(register int i=0; i<lglg; i++) {
			int p=v[i+lg];
			for(register int j=0; j<lg; j++)if(j&(1<<i))p^=v[j];
			fake+=p<<i;
		}
		v[fake]^=1;
	}
	for(register int i=0; i<lg; i++)if(v[i])bit&=b[i];
	cout<<bit._Find_first()+1<<endl;
	return 0;
}
```

---

## 作者：SpeMars (赞：5)

sto毒水出题人orz。

神仙构造，原型部分为微软某年~~我忘了~~的公司面试题。

其实就是去掉了变异鼠，直接二进制分组即可。

我们令老鼠复杂度为 $\operatorname{M}(x)$。

# 1pts:

没有老鼠，只有一瓶药。

```cpp
puts("1");
```
老鼠复杂度 $\operatorname{M}(0)$。

# 10pts:

显然每瓶药用三只老鼠去尝试，如果死了两只或以上的就是毒水。

老鼠复杂度 $\operatorname{M}(3n)$。

# 30pts:

对于每瓶药都用 $3$ 只老鼠太浪费了，我们考虑二进制拆分。

对于每一只老鼠 $i$，让它去喝二进制该位为 $1$ 的药水。

最后合并所有二进制的结果，得到毒水编号。

由于变异鼠的存在，所以每个二进制位要用 $3$ 只老鼠检验。

注意老鼠编号从 $1$ 开始，二进制拆分时，注意整体偏移编号。

老鼠复杂度 $\operatorname{M}(3 \log n)$。

# 100pts:

我们每个二进制位都用 $3$ 只老鼠检验显然也很浪费。

我们是否可以用二进制拆分的类似方法确定变异鼠的位置？

然后对其取反，再合并二进制信息，得到毒水编号。

老样子，我们先用 $\log n$ 只老鼠喝对应二进制位。

然后对这几只老鼠二进制分组。

再用 $\log {\log n}$ 只老鼠喝他们之间毒水的异或。

这里异或可能会对理解不太友好,~~作者也是~~。

为了方便，我们对老鼠分三六九等：

我们称最先的二进制拆分毒水的老鼠为普通鼠。

新增的这 $\log {\log n}$ 只老鼠被称为队长鼠。

最后那一只为主席鼠。

对于每只队长鼠喝它管辖的普通鼠的水的异或就是指，

保证这只队长鼠鼠把它所管辖的普通鼠所喝的水中喝了奇数次的都喝一遍。

这样每只新增的队长鼠及其管辖的普通鼠喝的每瓶水都会被不同的偶数只老鼠喝。

最后再用主席鼠喝每只队长鼠喝的水的异或，可以理解为队长的队长。

这样每个小队中每瓶水都会被不同的偶数只老鼠喝到。

那么我们先看变异鼠是否在队长鼠或主席鼠之间。

结论：如果每一只老鼠队伍中老鼠一共死了奇数只，那么他们中间出现变异鼠。

证明也很简单：

假设这个队喝的水中出现毒水，如果没有变异鼠，那么一定死去偶数只老鼠。

如果有变异鼠，变异鼠不死，所以会死奇数只老鼠。

又假设他们喝的水中没有毒水，如果没有变异鼠，那么全部不死，也是死了偶数只。

如果有变异鼠，那么就只有这一只老鼠因没喝到毒水而死，所以死 $1$ 只，也是奇数只。

证毕。

所以如果所有队长鼠和主席鼠这只队伍间死了奇数只，那么前面的毒水二进制拆分不会有问题。

否则，我们就每一队每一队地检查。

确定每队中是否出现变异鼠，然后再取并集，也就是用二进制还原。

找到这只鼠后就把它的状态取反即可。

tips:由于用 $1$ 作为二进制拆分的标准会导致浪费 $0$ 这个点，所以我们用 $0$ 来拆分。

老鼠复杂度：$\operatorname{M}(\log n+\log {\log n}+1)$。

az,介于作者太菜且语文很差说的有点抽象……~~(浅喷)~~。

# AC code:

```cpp
 #include<cmath>
 #include<cstdio>
 #include<cstring>
 #include<iostream>
 using namespace std;
 const int N=1010; 
 int n,mx,t[N],d[N][N],sd[N],z[N][N],sz[N],r[N],a,b,ljh,laq,ans;
 signed main(){
	scanf("%d%d",&n,&mx);
	if(n==1){
		puts("2");
		fflush(stdout);
		puts("1");
		return (0^0);
	}
	a=ceil(log2(n)),b=ceil(log2(a)),ans=(1<<a)-1,ljh=a+b,laq=(1<<b)-1;
//	printf("%d\n",ljh);
	for(int i=0;i<a;++i){
		for(int j=0;j<n;++j){
			if(!((1<<i)&j)){
				d[i][++sd[i]]=j;
			}
		}
	}
	for(int i=a;i<ljh;++i){
		for(int j=0;j<a;++j){
			if(!(j&(1<<(i-a)))){
				z[i][++sz[i]]=j;
				for(int k=1;k<=sd[j];++k)++t[d[j][k]];
			}
		}
		for(int j=0;j<n;++j)if((t[j]&1))d[i][++sd[i]]=j;
		memset(t,0,sizeof(t));
	}
	for(int i=a;i<ljh;++i)for(int j=1;j<=sd[i];++j)++t[d[i][j]];
	for(int i=0;i<n;++i)if((t[i]&1))d[ljh][++sd[ljh]]=i;
	for(int i=0;i<=ljh;++i){
		printf("1 %d ",sd[i]);
		for(int j=1;j<=sd[i];++j)printf("%d ",d[i][j]+1);
		puts("");
	}
	puts("2");
	fflush(stdout);
	for(int i=0;i<=ljh;++i)scanf("%d",r+i);
	int cnt=0;
	for(int i=a;i<=ljh;++i)cnt+=(r[i]==0);
	if(cnt&1){
		for(int i=0;i<a;++i){
			if(r[i]==0)ans=(ans^(1<<i));
		}
	}
	else{
		for(int i=a;i<ljh;++i){
			int cnt=(r[i]==0);
			for(int j=1;j<=sz[i];++j)cnt+=(r[z[i][j]]==0);
			if(cnt&1)laq=(laq^(1<<(i-a)));
		}
		r[laq]^=1;
//		printf("%d\n",laq);
		for(int i=0;i<a;++i){
			if(r[i]==0)ans=(ans^(1<<i));
		}
	}
	printf("%d\n",(ans+1));
	return (0^0);
 }
```

---

## 作者：xh39 (赞：2)

## 序
为方便，此篇题解**所有编号从 $0$ 开始。二进制位是从右往左数的。** 所有 $log_2(n)$ 都是向上取整。

前置基础:请确保学完了基础语言(if,for,二维数组)，建议先学习分治(这样更看得懂一些)。最好学过基本位运算(可以不学，但实现起来会麻烦一些)。

这道题非常有趣 ~~(毒瘤)~~，其实没有什么算法难度，但确实思维难度高。考虑**简化**题目。从简单情况入手，从暴力开始，逐步推出正解。

附基础位运算:

查询 $a$ 的第 $b$ 个二进制位的值:```(a>>b)&1```。

将 $a$ 的第 $b$ 二进制位修改为 $c$ ($a$ 初始第 $b$ 位为 $0$): ```a|=(c<<b);```
## 简化题目:立即得到结果，无变异鼠

假设可以询问一次就立刻得到答案。并且没有变异鼠。

这就可以利用分治解决。**先把这 $n$ 瓶水均分成两部分。并且让一只老鼠喝掉其中的一部分。如果这个老鼠中毒了，那么就说明这一部分有毒，否则说明另一部分有毒。**

注:为避免出现一段区间大小为奇数。先将 $n$ 变为**最小**但**大于等于** $n$ 的 $2^{k} (k为整数)$。

确定了有毒的一部分后，另一部分就可以丢开了。这样问题的规模就缩小了一半。

举个例子。现在有 $13$ 瓶水，编号为 $0～15$。

先将其均分成两截，分别为 $[0,7]$ 与 $[8,15]$ 。

让一只老鼠把 $[0,7]$ 都喝一遍，假设它中毒了，那么毒水一定在 $[0,7]$ ，否则在 $[8,15]$。

假设没中毒，那么再将 $[8,15]$ 分成两截 $[8,11]$ 与 $[12,15]$。再让一只老鼠喝 $[8,11]$。每次范围都可以缩小一半，所以可以在 $log_2(n)上取整$ 的询问次数内求出毒水。

## 简化题目:无变异鼠
这一部分感觉自己讲得不好，可以结合其它题解或自己画图理解。

现在不能立刻得到实验结果。那么应该怎么办呢?

假设还是区间 $[0,15]$，分成了 $[0,7]$ 和 $[8,15]$。

由于不知道毒水在哪一边，所以每一部分是毒水的情况都得试一次。即让一只老鼠既喝下 $[0,3]$，又喝下 $[8,11]$。假设毒水经判断在 $[0,8]$，那么 $[8,11]$ 部分对结果不会产生影响。那么可以相当于这只老鼠只喝了 $[0,3]$ 这部分。也就是与之前一样地判断了。然后再让一只老鼠喝 $0,1,4,5,8,9,12,13$。最后让一只老鼠喝 $0,2,4,6,8,10,12,14$。

换一个理解方式，就是**不断确定第 $i$ 位的二进制。首先枚举每一位，喝下满足 编号 在该位 二进制位 $0$ 的所有水。若中毒则毒水在此位二进制为 $0$。否则毒水在此位二进制为 $1$。** 这样实现起来会比之前的递归会方便很多。

该部分的核心代码是:
```cpp
int main(){
	for(i=0;i<logn;i++){ //从右往左数第i位。
		sum=0;
		for(j=0;j<n;j++){ //第j瓶水。
			if(!((j>>i)&1)){ //算出要询问多少只老鼠。(j>>i)&1表示查询j从右往左数第i个二进制位的值。
				sum++;
			}
		}
		cout<<"1 "<<sum<<" ";
		for(j=0;j<n;j++){
			if(!((j>>i)&1)){
				cout<<j+1<<" "; //注意要加一，因为题目从1开始编号。
			}
		}
		cout<<endl;
	}
	for(i=0;i<m;i++){
		scanf("%d",live+i);
	}
	for(i=0;i<logn;i++){ 
		ans|=(live[i]<<i); //第i此询问的是毒水编号的第i位。
	}
	cout<<ans+1;
}
```
## 暴力 $(2log_2(n)+1)$ 次询问 ($21$ 次)
现在有变异鼠了，又怎么对付?由于只有1只变异鼠，所以简单的办法是**重复**实验~~避免偶然性~~。即每个二进制位用 $2$ 只老鼠来检验。

那么最多要重复几次呢?只需要 $2$ 次就够了。因为只有 $1$ 只变异鼠，不可能 $2$ 次询问的结果都错了。但是如果 $2$ 次查询的结果不一样，那么说明有一只老鼠是错的。于是就要额外 $1$ 只。

但是如果最后一次询问是变异鼠，那么最坏会把你卡到 $21$ 次询问。

## 正解 $(log_2(n)+log_2^2(n)+1)$ 次询问($15$ 次)

上一个算法每次询问都需要重新用一个来寻找。现在可以考虑继续分治。

也就是说，是不是可以考虑每次逐步按照之前的方法确定变异鼠编号所在的二进制位。

比如，假设用了 $4$ 只老鼠，先检测第 $0,2$ 只是否有变异鼠。再检测 $0,1$ 只是否有变异鼠。

但是有个问题，如何确定许多只老鼠里是否有变异鼠?

可以仿照之前的暴力算法，**让每瓶水都喝偶数次。**

称之前第一次询问的老鼠为询问鼠，现在用于检测的老鼠为检测鼠。

要检测许多只老鼠中是否有变异鼠，就新用一个检测鼠，再枚举每一瓶水，**若这瓶水被这些老鼠喝了奇数次，就让检测鼠喝下**。保证每瓶水都被喝偶数次。

这样有什么好处呢?每瓶水都出现了偶数次，那说明**如果其中不存在变异鼠，则这里面一定有偶数只老鼠死亡**，因为毒水会被偶数只老鼠喝下。而**如果存在变异鼠，那么一定有奇数只死亡**，因为只有一次询问的结果会因变异鼠错误。

但是还要考虑一个问题，检测鼠中也可能有变异鼠，所以还需要新开一只老鼠来检测所有检测鼠中是否有变异鼠。但是只需要一只，因为我们的目标不需要找出变异鼠。**若发现此次询问有奇数只老鼠死亡**，变异鼠在检测鼠或这只老鼠中，那么询问鼠全部正常，**直接用询问鼠的结果**。**若有偶数只死亡**，说明检测鼠全部正常。那么**直接用检测鼠的结果，反转找出变异的询问鼠的结果，再得出答案**。

## 代码
(初学者可能看不懂这份代码)

题解实现保证喝偶数次的操作可以用异或实现。中为异或方便用了bitset。这样会方便一些。
```cpp
#include<iostream>
#include<bitset>
using namespace std;
bitset<1025> zyl[25],zero=0,one=1,tkr,zxr;
int size[2017];
bool live[2017];
int main(){
	int n=1000,m,i,j,logn,log2n,cuo=0,ans=0,sum=0; //cuo:变异鼠。
	bool ykb=0; 
	cin>>n>>i;
	for(logn=1;(2<<logn)<n;logn++){}
	logn++;
	for(log2n=1;(2<<log2n)<logn;log2n++){}
	log2n++;
	m=logn+log2n+1;
	for(i=0;i<logn;i++){ //询问鼠
		sum=0;
		for(j=0;j<n;j++){
			if(!((j>>i)&1)){
				sum++;
			}
		}
		cout<<"1 "<<sum<<" ";
		for(j=0;j<n;j++){
			if(!((j>>i)&1)){
				cout<<j+1<<" ";
				zyl[i]|=(one<<j); //记录下喝了哪些水。
			}
		}
		cout<<endl;
	}
	for(i=0;i<log2n;i++){ //检测鼠。
		tkr=0;
		for(j=0;j<logn;j++){
			if(!((j>>i)&1)){
				tkr^=zyl[j]; //异或可以保证奇数为1,偶数为0。就可以知道哪些水喝了奇数次。
			}
		}
		sum=0;
		cout<<"1 "<<tkr.count()<<" ";
		for(j=0;j<n;j++){
			if((tkr&(one<<j))!=zero){
				cout<<j+1<<" ";
				zyl[logn+i]|=(one<<j);
			}
		}
		cout<<endl;
		zxr^=tkr;
	}
	cout<<"1 "<<zxr.count()<<" "; //检测 检测鼠 的老鼠
	sum=0;
	for(j=0;j<n;j++){
		if((zxr&(one<<j))!=zero){
			cout<<j+1<<" ";
		}
	}
	cout<<endl<<"2"<<endl;
	for(i=0;i<m;i++){
		scanf("%d",live+i);
	}
	for(i=logn;i<m;i++){
		ykb^=!live[i];
	}
	if(!(ykb&1)){ //如果变异鼠不存在于检测鼠中。
		for(i=0;i<log2n;i++){
			ykb=!live[i+logn]; //如果这只老鼠死了，那么ykb初始就为1。因为当前检测鼠也要算进去。
			for(j=0;j<logn;j++){
				if(!((j>>i)&1)){
					ykb^=!live[j];
				}
			}
			if(!(ykb&1)){ //如果没检测出来，说明这个二进制位是1。检测出来了不需要操作，因为初始值就是0。
				cuo|=(1<<i);
			}
		}
		live[cuo]=!live[cuo]; //反转错误的答案。
	}
	for(i=0;i<logn;i++){ 
		ans|=(live[i]<<i);
	}
	cout<<ans+1;
	return 0;
}
```
然后就可以得到 $99$ 分了。

原来是需要特判 $n=1$ 的情况。因为 $n=1$ 时按这种方法需要 $1$ 次询问。

特判相信大家都会，所以就不给代码了。

这题是一道非常好的题。这次比赛整体质量也特别高。

---

## 作者：Oracynx (赞：1)

## P7824 「RdOI R3」毒水 题解

### 思路分析

显然的，如果没有变异鼠的存在，这道题就是一道很经典的二进制分组。

考虑找出变异鼠。

显然的，我们需要先用 $\log_2 n = 10$ 只老鼠来对 $n$ 瓶水进行分组，记为一级鼠。

```cpp
for (int i = 0; i < n; i++)
{
    int x = i;
    int id = 0;
    for (; x != 0;)
    {
        if (x & 1)
        {
            need[id].push_back(i + 1);
        }
        x /= 2;
        id++;
    }
}
k = 0;
for (int i = 0;; i++)
{
    if (need[i].size() == 0)
    {
        break;
    }
    k++;
    printf("1 %zu", need[i].size());
    for (auto x : need[i])
    {
        printf(" %d", x);
    }
    printf("\n");
}
```

考虑变异鼠在一级鼠中。

不看那 $n$ 瓶水，我们得到了一个子问题，如何用 $\le 5$ 只老鼠数量来对 $10$ 只老鼠进行校验。

我们考虑对一级鼠老鼠进行二进制分组，每一只二级鼠喝掉其管辖的所有老鼠中出现了奇数次的水。

```cpp
for (int i = 0; i < k; i++)
{
    int x = i;
    int id = 0;
    for (; x != 0;)
    {
        if (x & 1)
        {
            for (auto k : need[i])
            {
                need2[id].push_back(k);
            }
        }
        x /= 2;
        id++;
    }
}
int k2 = 0;
for (int i = 0;; i++)
{
    unique(need2[i]);
    if (need2[i].size() == 0)
    {
        break;
    }
    k2++;
    printf("1 %zu", need2[i].size());
    for (auto x : need2[i])
    {
        printf(" %d", x);
    }
    printf("\n");
}
```

但这时我们无法知道变异鼠在一级鼠还是二级鼠中，所以我们引入一只三级鼠，管辖所有的二级鼠。

由于我们只需要知道二级鼠是否正确，所以我们不再需要 $\log_2\log_2\log_2 n$ 只老鼠。

如果二级鼠的异或和与三级鼠一致，则变异鼠在一级鼠中。

```cpp
if (x2 == p[k + k2])
{
    int bad = 0;
    for (int i = 0; i < k2; i++)
    {
        bool t = p[k + i] == 1;
        for (int j = 0; j < k; j++)
        {
            if ((j >> i) & 1)
            {
                t ^= p[j] == 1;
            }
        }
        if (t)
        {
            bad |= 1 << i;
        }
    }
    p[bad] ^= true;
}
```

否则变异鼠在二级鼠或者三级鼠中，我们可以直接使用一级鼠的信息。

```cpp
int answer = 0;
for (int i = 0; i < k; i++)
{
    if (p[i])
    {
        answer |= 1 << i;
    }
}
printf("%d\n", answer + 1);
```

本文的纠错方式类似于「[汉明码](https://zh.wikipedia.org/wiki/汉明码)」，可自行查阅。

总的老鼠数量 $\lceil\log_21000\rceil + \lceil\log_2\log_21000\rceil + 1 = 10 + 4 +1 = 15$。

### 代码实现

本文将 $p_i$ 取反是因为我从一开始就理解反了，所以这么改简单一些。

```cpp
#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
constexpr int MaxN = 1e3 + 5;
int n;
std::vector<int> all;
std::vector<int> need[MaxN];
std::vector<int> need2[MaxN];
void unique(std::vector<int> &vec)
{
    std::vector<int> res;
    std::map<int, bool> map;
    for (auto k : vec)
    {
        map[k] ^= true;
    }
    for (auto k : vec)
    {
        if (map[k])
        {
            res.push_back(k);
            map[k] = false;
        }
    }
    vec = res;
    std::sort(vec.begin(), vec.end());
}
int main()
{
    scanf("%d%*d", &n);
    if (n == 1)
    {
        printf("2\n");
        printf("1\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        int x = i;
        int id = 0;
        for (; x != 0;)
        {
            if (x & 1)
            {
                need[id].push_back(i + 1);
            }
            x /= 2;
            id++;
        }
    }
    int k = 0;
    for (int i = 0;; i++)
    {
        if (need[i].size() == 0)
        {
            break;
        }
        k++;
        printf("1 %zu", need[i].size());
        for (auto x : need[i])
        {
            printf(" %d", x);
        }
        printf("\n");
    }
    for (int i = 0; i < k; i++)
    {
        int x = i;
        int id = 0;
        for (; x != 0;)
        {
            if (x & 1)
            {
                for (auto k : need[i])
                {
                    need2[id].push_back(k);
                }
            }
            x /= 2;
            id++;
        }
    }
    int k2 = 0;
    for (int i = 0;; i++)
    {
        unique(need2[i]);
        if (need2[i].size() == 0)
        {
            break;
        }
        k2++;
        printf("1 %zu", need2[i].size());
        for (auto x : need2[i])
        {
            printf(" %d", x);
        }
        printf("\n");
    }
    for (int i = 0; i < k2; i++)
    {
        for (auto k : need2[i])
        {
            all.push_back(k);
        }
    }
    unique(all);
    printf("1 %zu", all.size());
    for (auto x : all)
    {
        printf(" %d", x);
    }
    printf("\n");
    printf("2\n");
    fflush(stdout);
    int p[MaxN];
    for (int i = 0; i < k + k2 + 1; i++)
    {
        scanf("%d", &p[i]);
        p[i] = !p[i];
    }
    int x1, x2;
    x1 = 0;
    x2 = 0;
    for (int i = 0; i < k; i++)
    {
        x1 ^= p[i];
    }
    for (int i = k; i < k + k2; i++)
    {
        x2 ^= p[i];
    }
    if (x2 == p[k + k2])
    {
        int bad = 0;
        for (int i = 0; i < k2; i++)
        {
            bool t = p[k + i] == 1;
            for (int j = 0; j < k; j++)
            {
                if ((j >> i) & 1)
                {
                    t ^= p[j] == 1;
                }
            }
            if (t)
            {
                bad |= 1 << i;
            }
        }
        p[bad] ^= true;
    }
    int answer = 0;
    for (int i = 0; i < k; i++)
    {
        if (p[i])
        {
            answer |= 1 << i;
        }
    }
    printf("%d\n", answer + 1);
    return 0;
}
```

---

## 作者：红黑树 (赞：1)

[可能更好的阅读体验](https://rbtree.archi/intr-inter.html)

## [题意](https://www.luogu.com.cn/problem/P7824)
有 $n$ 瓶水，其中一瓶有毒。
有 $maxk$ 只小白鼠，其中有一只变异了。现在要决定每只小白鼠喝哪些水。最后给出每只小白鼠的死亡情况，你需要输出毒水的编号。
普通小白鼠喝毒水会死，变异小白鼠不喝毒水会死。

## 题解
### Subtask 1
直接输出 $1$。

[代码](https://rbtree.archi//lib/Code/Other/2.txt)

### Subtask 2
每瓶水用 $3$ 只小白鼠试，如果死了 $2$ 只或 $3$ 只的就是毒水。

小白鼠用量 $3n$。

[代码](https://rbtree.archi//lib/Code/Other/3.txt)

### Subtask 3
对于第 $i$ 只小白鼠，让它去试所有编号二进制第 $i$ 位为 $1$ 的水。当然，因为有变异小白鼠的存在，要用 $3$ 只试。

小白鼠用量 $3 \log n$。

[代码](https://rbtree.archi/lib/Code/Other/4.txt)

### Subtask 4 & 5
注意到变异鼠就是普通老鼠取反，因此我们要考虑确定变异鼠的位置。

和 Subtask 3 一样，我们用第 $j$ 只小白鼠来检测所有编号二进制第 $j$ 位为 $1$ 的小白鼠。

检验方法就是和这些小白鼠喝的水集合的异或，然后再把死亡情况异或起来，若为 $1$，则表示有矛盾。

因为每瓶水都被喝了偶数次，因此异或起来一定是 $0$，由于有一只变异，所以出现差错的话异或起来一定是 $1$。

然后注意到我们无法判断变异鼠是在检测鼠当中还是实验鼠当中，不过注意到我们还剩一只没有用，拿它来检测即可。

小白鼠用量 $\log n + \log \log n + 1$。

[代码](https://rbtree.archi/lib/Code/Other/5.txt)

### 全部 Subtask
用 Subtask 4 & 5 的方法，注意特判 Subtask 1。

## [代码](https://rbtree.archi/lib/Code/Luogu/P7824.txt)

---

## 作者：whiteqwq (赞：1)

[P7824 「RdOI R3」毒水](https://www.luogu.com.cn/problem/P7824)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1816498)

## 题意

$n$ 瓶水，其中一瓶有毒，你可以检测若干次，每次选择若干瓶水，检测其中是否有毒水，但有且仅有一次检测结果会反过来，你需要在 $maxk$ 次检测内找出毒水。注意，结果不是实时得到，当你询问结束后才能一次性得到所有结果。

（$1\leqslant n\leqslant 1000,1\leqslant maxk\leqslant 15$）

## 分析

交互杀我！！！

$10pts$：很容易把每一瓶水检验三次，只要有两次检验出来就一定是毒水。

$30pts$：考虑没有那次反过来的检测如何求，我们可以直接检测每个二进制位是否有毒水，然后拼起来就好了，如果有那次反过来的检测，检测三次就可以避免。

$100pts$：检验三次消耗过大，考虑快速检验二级制位。

我们用 $\log \log n$ 次检测对二进制位的检测再次二进制拆分，然后再用 $1$ 次检测作为新加入的检测的异或。

很容易发现如果反转不在新加入的 $\log\log n+1$ 个检测，那么这 $\log\log n+1$ 个检测的死亡数为偶数。于是如果其为偶数，我们可以直接找到反转在前 $\log n$ 个检测中的位置，否则前 $\log n$ 个检测可以直接算。

检测次数 $\log n+\log\log n+1$，符合要求。

## 代码
```
#include<stdio.h>
#include<bitset>
#include<math.h>
using namespace std;
const int maxn=1005,maxk=15;
int n,k,lg,lglg;
int v[maxk];
bitset<maxn>ans,b[maxk];
int main(){
	scanf("%d%d",&n,&k);
	if(n==1&&k==0){
		puts("2"),fflush(stdout);
		puts("1"),fflush(stdout);
		return 0;
	}
	lg=log2(n-1)+1,lglg=log2(lg-1)+1;
	for(int i=0;i<lg;i++){
		for(int j=0;j<n;j++)
			if((j>>i)&1)
				b[i][j]=1;
		printf("1 %d ",b[i].count());
		for(int j=0;j<n;j++)
			if(b[i][j])
				printf("%d ",j+1);
		puts(""); 
	}
	for(int i=0;i<lglg;i++){
		for(int j=0;j<lg;j++)
			if((j>>i)&1)
				b[lg+i]^=b[j];
		printf("1 %d ",b[lg+i].count());
		for(int j=0;j<n;j++)
			if(b[lg+i][j])
				printf("%d ",j+1);
		puts("");
	}
	for(int i=0;i<lglg;i++)
		b[lg+lglg]^=b[lg+i];
	printf("1 %d ",b[lg+lglg].count());
	for(int i=0;i<n;i++)
		if(b[lg+lglg][i])
			printf("%d ",i+1);
	puts("\n2"),fflush(stdout);
	for(int i=0;i<=lg+lglg;i++)
		scanf("%d",&v[i]);
	int ok=0;
	for(int i=0;i<=lglg;i++)
		ok^=(v[lg+i]^1);
	if(ok==0){
		int pos=0;
		for(int i=0;i<lglg;i++){
			int ook=(v[lg+i]^1);
			for(int j=0;j<lg;j++)
				if((j>>i)&1)
					ook^=(v[j]^1);
			pos+=(ook<<i);
		}
		v[pos]^=1;
	}
	ans.set();
	for(int i=0;i<lg;i++)
		if(v[i]==0)
			ans&=b[i];
	for(int i=0;i<n;i++)
		if(ans[i]){
			printf("%d\n",i+1),fflush(stdout);
			break;
		}
	return 0;
}
```

---

## 作者：Demoe (赞：1)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/P7824)

## $\text{Description}$

- 有 $n$ 瓶水，其中有 $1$ 瓶毒水。你最多可以用 $maxk$ 只老鼠，每只老鼠可以喝任意多的水。
- 在你选的老鼠之中，恰有一只老鼠变异了，当它喝到了毒水不会死，喝不到毒水才会死。
- 给出你选的老鼠的存活情况，问哪个是毒水。

## $\text{Solution}$

观察到有 $2^9<n<2^{10}$。

大概一看就是考虑二进制分组了。

$1\sim n$ 标号不太方便，我们改成 $0\sim n-1$

先看 $maxk=30$ 的限制。

我们先选 $10$ 只鼠编号为 $0\sim 9$，让它们分别喝对应的水，编号为 $i$ 的鼠喝的水的编号转化为二进制 $2^i$ 这一项系数为 $1$。

考虑到变异鼠，我们每个鼠复制一下成三个鼠，这样就能辨别出变异鼠了。

然后考虑去掉变异鼠每个鼠存活情况，编号为 $i$ 的鼠存活当且仅当毒水编号转化为二进制后 $2^i$ 这一项系数为 $0$。

然后算出来即可。

然后考虑 $maxk=15$。

显然不是 $\dfrac{maxk}{2}$ 的关系，因为这没啥实际意义。

很容易想到 $\left\lceil \log_2n \right\rceil+\left\lceil \log_2\left\lceil \log_2n \right\rceil \right\rceil=14$，盲猜是 $\left\lceil \log_2n \right\rceil+\left\lceil \log_2\left\lceil \log_2n \right\rceil \right\rceil+1=15$。

$\left\lceil \log_2\left\lceil \log_2n \right\rceil \right\rceil$ 这个东西容易想到是对上面我们鼠的编号再二进制分组。

考虑一些水的集合 $S$ 和一些鼠的集合 $M$，保证对于 $\forall s\in S$ 水 $s$ 被 $M$ 中偶数个鼠喝了，且对于 $\forall m\in M$ 鼠 $m$ 喝的水都在 $S$ 中。

有结论若 $M$ 中死了偶数个则无变异鼠，若 $M$ 中死了奇数个则有变异鼠。由定义和恰有一瓶毒水一只变异鼠易证。

那么考虑对 $0\sim 9$ 这些鼠再进行类似地二进制分组，编号为 $10+i$ 的鼠喝的水为编号转化为二进制后 $2^i$ 系数为 $1$ 的**鼠**喝的水的**异或**。（异或有很好的性质能保证每瓶水被喝偶数次。）

为防止这 $10\sim 13$ 四只鼠里有内鬼，再拿一只鼠喝他们喝的水的异或即可。

然后先考虑 $10\sim 14$ 这里有无内鬼，若有则表明 $0\sim 9$ 里无内鬼，直接用上面 $maxk=30$ 的方法算即可。

若 $10\sim 14$ 无内鬼，则考虑 $10\sim 13$ 和它们各自支配的鼠，分别考虑是否有内鬼，若 $10+i$ 和支配的鼠里有内鬼，则表明内鬼鼠编号转化为二进制后 $2^i$ 系数为 $1$。把内鬼算出来然后直接把它存活状态取反即可。然后还像上面一样算出毒水即可。

记得 $n=1/2$ 拿出来特判。

记得 `cout` 不知道为啥之前不用 `cout` 基本全 T 了。

## $\text{Code}$

```cpp
const int N=1005,M=20;
int n,q,sum1,sum2,s[M],qaq;bool op;
bitset<N> a[M],ans;

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;ans.set();
	if(n==1){cout<<2<<endl<<1<<endl;return 0;}
	if(n==2){cout<<"1 1 1"<<endl<<2<<endl;cin>>q;cout<<2-q<<endl;return 0;}
	sum1=log2(n-1)+1;sum2=log2(sum1-1)+1;
	for(re i=0;i<sum1;++i){
		for(re j=0;j<n;++j) a[i][j]=(j>>i)&1;cout<<"1 "<<a[i].count()<<' ';
		for(re j=0;j<n;++j) if((j>>i)&1) cout<<j+1<<' ';cout<<endl;
	}
	for(re i=0;i<sum2;++i){
		for(re j=0;j<sum1;++j) if((j>>i)&1) a[sum1+i]^=a[j];cout<<"1 "<<a[sum1+i].count()<<' ';
		for(re j=0;j<n;++j) if(a[sum1+i][j]) cout<<j+1<<' ';cout<<endl;a[sum1+sum2]^=a[sum1+i];
	}
	cout<<"1 "<<a[sum1+sum2].count()<<' ';
	for(re j=0;j<n;++j) if(a[sum1+sum2][j]) cout<<j+1<<' ';cout<<endl<<2<<endl;
	for(re i=0;i<=sum1+sum2;++i) cin>>s[i],s[i]^=1,op^=i>=sum1?s[i]:0;
	if(!op){
		for(re i=0;i<sum2;++i){
			q=s[sum1+i];for(re j=0;j<sum1;++j) q^=((j>>i)&1)?s[j]:0;qaq+=q<<i;
		}
		s[qaq]^=1;
	}
	for(re i=0;i<sum1;++i) if(s[i]) ans&=a[i];cout<<ans._Find_first()+1<<endl;
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：huazai676 (赞：0)

std 的构造很巧妙啊，有类似的想法但没搞出来。于是可以从「**信息**」的角度直接考虑这类问题。

已知每只小白鼠的死或活，一瓶水的信息可以表示为喝了这瓶水的小白鼠的集合。假设没有变异小白鼠，只要任意两瓶水的信息不一样便可以找到毒水。$k$ 只小白鼠对应 $2^k$ 个集合，也就是可以区分 $2^k$ 瓶水。

但当存在一只变异小白鼠时，两瓶水的信息不相同已经不够区分了。假设某只小白鼠喝了 $a$ 没喝 $b$，该小白鼠的活或死分别指示了“$a$ 不是毒药”或“$b$ 不是毒药”。假设不相同的信息数量小于等于 2 时，即对于喝 $a$ 和喝 $b$ 的小白鼠集合 $A$ 和 $B$，$|A \oplus B|=|(A \setminus B)\cup(B \setminus A)| \leq 2$，无法区别这两只（或更少）不同小白鼠中有无变异。毒药如果就是这两瓶水之一，信息则不足以区分。所以对于任意两集合，不同信息数量要大于 2。因为只有一个信息是假的，所以选多数信息所指示的含义即可。

于是问题转换为：从 $\set{1,2,\dots ,k}$ 中能最多选多少个子集，使得对于任意两子集 $A$ 和 $B$，$|A \oplus B|>2$。发现 $k=15$ 的时候，把 $0,1,\dots ,2^k-1$ 代表的集合依次尝试加入判合法就可以加 2048 个；$k=14$ 时这样能加 1024 个；$k=7$ 能加16个。然后就做完了，复杂度是 $O(n2^{\min(k,14)})$。

代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>

using namespace std;

const int N=1010;

int n,m;
int st[N],tp;
vector<int> buc[16];
int r[16];

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    m=min(m,14);

    for(int i=0;i<(1<<m);i++)
    {
        if(tp>=n) break;
        bool ok=true;
        for(int j=1;j<=tp;j++)
        {
            if(__builtin_popcount(i^st[j])<=2)
            {
                ok=false;
                break;
            }
        }
        if(ok) st[++tp]=i;
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++)
            if(st[i]>>j&1)
                buc[j].push_back(i);
    for(int i=0;i<m;i++)
    {
        if(buc[i].size()==0) buc[i].push_back(1);
        cout<<1<<' '<<buc[i].size()<<' ';
        for(int t:buc[i]) cout<<t<<' ';
        cout<<endl;
    }
    cout<<2<<endl;
    for(int i=0;i<m;i++) cin>>r[i],r[i]^=1;
    int now=1;
    for(int i=2;i<=n;i++)
    {
        int x=st[now]^st[i];
        int cnt=0;
        for(int j=0;j<m;j++)
        {
            if(x>>j&1)
            {
                if((st[i]>>j&1)^r[j]) cnt++;
                else cnt--;
            }
        }
        if(cnt<0) now=i;
    }

    cout<<now<<endl;

    return 0;
}
```

---

## 作者：psoet (赞：0)

乱搞做法。

令 $S_i$ 表示喂了第 $i$ 种药的老鼠集合（两两不同），$D$ 表示最终死了的老鼠集合。

如果第 $x$ 瓶药是毒药，第 $y$ 个老鼠是变种，那么 $D = S_x \oplus \{y\}$。

我们希望满足条件的 $x,y$ 是唯一的，也即不存在 $|S_i \oplus S_j| = 2$ 。

这是最大独立集问题。对于第五个子任务，直接把 $[0,2^k)$ 排成一列然后贪心就能得到一组解，甚至能做 $n = 4000$；第四个子任务比较紧，可以写一个独立集搜索算法。

复杂度不会算。

```cpp
#include <bits/stdc++.h>

#define For(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define rFor(i, b, a) for (int i = b, i##end = a; i >= i##end; --i)
#define eFor(i, u, v) for (int i = head[u], v = e[i].to; i; i = e[i].next, v = e[i].to)

typedef long long ll;
typedef std::pair<int, int> pii;
#define fi first
#define se second

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template<typename T> T myrand(T l, T r) {
	return std::uniform_int_distribution<T>(l, r)(rnd);
}

template<typename T, typename ...Args> void LOG(T x, Args ...args) {
#ifdef DEBUG
	fprintf(stderr, x, args...);
#endif
}

const int kS = 1 << 15 | 5;

int n, k, p[kS], a[kS];
std::vector<int> fed[20];
int vis[kS], clk;

std::vector<int> solve(std::vector<int> vert) {
	static int que[kS], hd, tl;
	if (vert.size() <= 1) return vert;
	std::vector<int> res;
	int p = vert[0], dp = 0;
	++clk;
	for (int u : vert) vis[u] = clk;
	For(i, 0, k - 1) For(j, i + 1, k - 1) if (vis[p ^ (1 << i) ^ (1 << j)] == clk) ++dp;
	for (int u : vert) if (u != p) {
		int deg = 0;
		For(i, 0, k - 1) For(j, i + 1, k - 1) if (vis[u ^ (1 << i) ^ (1 << j)] == clk) ++deg;
		if (deg > dp) p = u, dp = deg;
	}
	// Don't choose p
	int tclk = clk;
	if (p) {
		std::vector<int> tres;
		hd = 1, tl = 0;
		for (int s : vert) if (s != p && vis[s] == tclk) {
			std::vector<int> now(1, s);
			que[hd = tl = 1] = s;
			vis[s] = 0;
			while (hd <= tl) {
				int u = que[hd++];
				For(i, 0, k - 1) For(j, i + 1, k - 1) if (vis[u ^ (1 << i) ^ (1 << j)] == tclk && (u ^ (1 << i) ^ (1 << j) ^ p)) {
					que[++tl] = u ^ (1 << i) ^ (1 << j);
					vis[u ^ (1 << i) ^ (1 << j)] = 0;
					now.push_back(que[tl]);
				}
			}
			now = solve(now);
			for (int u : now) tres.push_back(u);
		}
		res = tres;
	}
	// Choose p
	std::vector<int> tres(1, p);
	for (int u : vert) vis[u] = tclk;
	For(i, 0, k - 1) For(j, i + 1, k - 1) if (vis[p ^ (1 << i) ^ (1 << j)] == tclk) vis[p ^ (1 << i) ^ (1 << j)] = 0;
	vis[p] = 0;
	for (int s : vert) if (s != p && vis[s] == tclk) {
		std::vector<int> now(1, s);
		que[hd = tl = 1] = s;
		vis[s] = 0;
		while (hd <= tl) {
			int u = que[hd++];
			For(i, 0, k - 1) For(j, i + 1, k - 1) if (vis[u ^ (1 << i) ^ (1 << j)] == tclk && (u ^ (1 << i) ^ (1 << j) ^ p)) {
				que[++tl] = u ^ (1 << i) ^ (1 << j);
				vis[u ^ (1 << i) ^ (1 << j)] = 0;
				now.push_back(que[tl]);
			}
		}
		now = solve(now);
		for (int u : now) tres.push_back(u);
	}
	if (tres.size() > res.size()) res = tres;
	return res;
}

int main() {
	scanf("%d%d", &n, &k);
	k = std::min(k, 15);
	if (n == 1) {
		printf("2\n"), fflush(stdout);
		printf("1\n"), fflush(stdout);
		return 0;
	}
	For(i, 0, (1 << k) - 1) p[i] = i;
	if (k > 7) {
		int cur = 0, clk = 0;
		std::shuffle(p, p + (1 << k), rnd);
		for (int i = 0; i < (1 << k); ++i) {
			bool ok = true;
			For(x, 0, k - 1) For(y, x + 1, k - 1)
				if (vis[p[i] ^ (1 << x) ^ (1 << y)]) {
					ok = false;
					break;
				}
			if (ok) a[++cur] = p[i], vis[p[i]] = true;
			if (cur == n) break;
		}
	}
	else {
		std::vector<int> vert(1 << k);
		std::iota(vert.begin(), vert.end(), 0);
		vert = solve(vert);
		assert(vert.size() >= n);
		fprintf(stderr, "sz = %u\n", vert.size());
		memset(vis, 0, sizeof(vis));
		For(i, 1, n) {
			a[i] = vert[i - 1];
			assert(!vis[a[i]]);
			vis[a[i]] = 1;
			For(x, 0, k - 1) For(y, x + 1, k - 1) assert(!vis[a[i] ^ (1 << x) ^ (1 << y)]);
		}
	}
	For(i, 1, n) For(j, 0, k - 1) if (a[i] >> j & 1) fed[j].push_back(i);
	For(i, 0, k - 1) {
		printf("1 %u", fed[i].size());
		for (int x : fed[i]) printf(" %d", x);
		printf("\n"), fflush(stdout);
	}
	int die = 0;
	printf("2\n"), fflush(stdout);
	For(i, 0, k - 1) {
		int x;
		scanf("%d", &x);
		die |= (!x) << i;
	}
	For(i, 1, n) For(j, 0, k - 1) if ((a[i] ^ (1 << j)) == die) {
		printf("%d\n", i), fflush(stdout);
		return 0;
	}
	return 0;
}
```

---

## 作者：Iam1789 (赞：0)

## 10 pts
每瓶水用 $3$ 只老鼠判断，如果某瓶水死了超过一只老鼠说明这瓶水有毒，证明显然。

## 30pts
对于前 $20$ 只老鼠，每 $10$ 只老鼠喝二进制下第 $i$ 位为 $1$ 的水，可以确定毒水的每一位，但可能有一位的误差。因此我们用第 $21$ 只老鼠喝每位异或为 $1$ 的水。因为变异鼠只会导致一位发生改变，所以异或值一定会改变，从而根据结果判断毒水。

## 70pts 
前 $10$ 只老鼠同 `30pts`，接着 $4$ 只老鼠喝**将二进制下该位为 $1$ 的位数异或和为 $1$ 的水。** 将二进制位从 $1$ 开始编号，水从 $0$ 开始编号，每瓶水都会在后 $4$ 只中喝一次。最后 $1$ 只老鼠喝编号按位异或为 $1$ 的水。每瓶水都会喝至少两次，因此如果前 $14$ 只的结果出现矛盾，可以用第 $15$ 只来判断哪只是正确的。这个可以将 `Sub5` 的次数卡到 $15$ 次。 但 `Sub4` 会多 $1$ 次。~~你多给一只不行吗~~

## 100pts
将二进制位从 $0$ 开始编号。这样就可以把第二部分的询问次数卡到 $2$ 次。但是由于在第二部分询问第 $0$ 位问不到，因此你就无法判定是第 $0$ 位有矛盾还是第 $7$ 只有矛盾。~~然后将询问顺序 `random_shuffle` 一下就能过了。~~ 前 $6$ 只显然无法优化，于是我们考虑更换第 $7$ 只。我们让第 $7$ 只老鼠喝第 $5$ 只和第 $6$ 只喝的水的异或。这样可以让每瓶水都被后 $3$ 只喝了偶数次，因此如果后 $3$ 只老鼠都正常，那么在这 $3$ 只中只会有偶数只死亡，我们选择后 $3$ 只给出的结果。如果变异鼠在后 $3$ 只里，会导致有奇数只老鼠死亡。我们直接选择前 $4$ 只给出的结果。该 `subtask` 最大询问次数 $7$ 次。

---

