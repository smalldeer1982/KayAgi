# Voting

## 题目描述

There are $ n $ employees in Alternative Cake Manufacturing (ACM). They are now voting on some very important question and the leading world media are trying to predict the outcome of the vote.

Each of the employees belongs to one of two fractions: depublicans or remocrats, and these two fractions have opposite opinions on what should be the outcome of the vote. The voting procedure is rather complicated:

1. Each of $ n $ employees makes a statement. They make statements one by one starting from employees $ 1 $ and finishing with employee $ n $ . If at the moment when it's time for the $ i $ -th employee to make a statement he no longer has the right to vote, he just skips his turn (and no longer takes part in this voting).
2. When employee makes a statement, he can do nothing or declare that one of the other employees no longer has a right to vote. It's allowed to deny from voting people who already made the statement or people who are only waiting to do so. If someone is denied from voting he no longer participates in the voting till the very end.
3. When all employees are done with their statements, the procedure repeats: again, each employees starting from $ 1 $ and finishing with $ n $ who are still eligible to vote make their statements.
4. The process repeats until there is only one employee eligible to vote remaining and he determines the outcome of the whole voting. Of course, he votes for the decision suitable for his fraction.

You know the order employees are going to vote and that they behave optimal (and they also know the order and who belongs to which fraction). Predict the outcome of the vote.

## 说明/提示

Consider one of the voting scenarios for the first sample:

1. Employee $ 1 $ denies employee $ 5 $ to vote.
2. Employee $ 2 $ denies employee $ 3 $ to vote.
3. Employee $ 3 $ has no right to vote and skips his turn (he was denied by employee $ 2 $ ).
4. Employee $ 4 $ denies employee $ 2 $ to vote.
5. Employee $ 5 $ has no right to vote and skips his turn (he was denied by employee $ 1 $ ).
6. Employee $ 1 $ denies employee $ 4 $ .
7. Only employee $ 1 $ now has the right to vote so the voting ends with the victory of depublicans.

## 样例 #1

### 输入

```
5
DDRRR
```

### 输出

```
D
```

## 样例 #2

### 输入

```
6
DDRRRR
```

### 输出

```
R
```

# 题解

## 作者：Cloud_Umbrella (赞：6)

   ~~终于找到一篇能写且自己也能写的题目了。~~
   
   这是一道很适合练手的队列题。但本人看了一下题解区，有很多都是用队列。这里介绍一种新的方法。
   ### 巧用下标
   这个方法不怎么高级，但挺适合新手。有点像用数组模拟队列。STL 虽然好用，但很费时间，永远没有手写的好（偶尔手写队列也可以锻炼一下自己）。
   
   准备两个指向 R 队和 D 队发言者下标的变量，再准备两个存储 R 队和 D 队长度的变量，直接模拟即可。
   
   另外提一嘴自增符，一种是先令变量自增，再改变表达式的值。一种是先改变表达式的值，再令变量自增。这两种不同的方法在代码中有不同的效果，视情况而定。
   
   具体过程看注释。
   ```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;  //静态定义MAXN，它的值不会改变。用科学计数法不但简洁，还不容易搞错。
int n;
char s;
int D[MAXN],R[MAXN];
int head_r=1,head_d=1;  // 用于记下标。 
int lend,lenr;          // 用于记长度。 
int main(){
	ios::sync_with_stdio(0); cin.tie(0),cout.tie(0); //本人认为这个加速器比scanf快亿分之一点点。 
    cin>>n;  //用了上面这行，拒绝scanf和printf。 
    for(int i=1;i<=n;i++){
        cin>>s;
        if(s=='D') D[++lend]=i;//分别记下他们的下标。
        else       R[++lenr]=i;
    }
    while(head_r<=lend && head_d<=lenr){//两队的下标都小于对方的长度，游戏就继续。
        if(D[head_r++]<R[head_d++]) D[++lend]=head_d+n; // 坐标越大越靠后。加n的原因感性理解就是回到队尾，等待下一次。 
        else R[++lenr]=head_d+n;                        
    }
    if(head_r>lend) cout<<"R";//R队的下标如若大于D队的长度，说明R队的某队员在最后面，所以不难理解，R队是最后的赢家。
	else cout<<"D";//反之亦然。
    return 0;   //好习惯伴终生。 
}  
   
   ```
   


---

## 作者：BINYU (赞：4)

### 先来理一遍题意：

1. 有两个党派，为 D、R。

2. 一个人**正常发言**时，能禁言一个人，被禁言的人**永远不能正常发言**。

3. 循环发言，直到只剩一个党派能发言为止。

------------


### 接着，我们来画一下发言流程图（如果不禁言）：

发言前：1 2 3 4 5

1 发言后：2 3 4 5 1

2 发言后：3 4 5 1 2

……

即每个人发言后，都排在队尾，队首发言。**这种题，不用队列都难**！

------------

### 再来看加了禁言的：

每个人当然会禁言下一个发言的“反派人物”，这样就不给他机会禁言“自己的同胞”，能最大限度地防止自己人被禁言。但这样不好直接处理禁言谁，队列只能对队首操纵……

**那就把两个党派还剩多少次禁言机会记下来呗，一有机会禁言，就用一次机会**

------------

### 注意：

一个党派的人都被禁言时，另一个党派可能不止一个人，所以不能用 ```!q.empty()``` 或 ```q.size()>1``` 来判断，必须**记录两派能发言的人数**，直到一方为零再停止。

------------


### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,r,d,cntr,cntd;
//r:R党禁言次数，d:D党禁言次数.
//cntr:R党现存多少人，cntd:D党现存多少人
char a;
queue <char> q;//生成队列
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>a;
		q.push(a);
		if(a == 'R')cntr++;//统计R党人数
		else cntd++;//统计D党人数
	}
	while(cntr > 0&&cntd > 0)//判断结束
		if(q.front() == 'D')//D党发言
			if(r >= 1)r--,q.pop(),cntd--;//被禁言
			else d++,q.push(q.front()),q.pop();//未被禁言
		else//R党发言
			if(d >= 1)d--,q.pop(),cntr--;//被禁言
			else r++,q.push(q.front()),q.pop();//未被禁言
	cout<<q.front();
	return 0;//好习惯
}

```

---

## 作者：wjr_jok (赞：2)

## 题意

有一个由 $D$ 和 $R$ 组成的字符串，从头到尾循环遍历，每遍历到一个字符踢出一个与它不同的字符，直到只剩下一个，输出这个字符。

## 思路

可以直接模拟，当然没必要每次都找到当前字符要踢出一个字符。我们可以用两个变量 $x,y$ 来记录已经遍历过的字符 $D,R$ 中有多少可以踢出字符的，如果对应的字符数量不为零，那么当前的字符就是可以被踢出的，否则就加到 $x,y$ 里面用于后续判断。

一个字符被踢出后就直接删除它，防止错误访问导致超时。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,a,b;
char s;
vector<int> xl;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s=='D'){
			xl.push_back(1); 
			a++;
		}//a记录未被禁言的D的个数
		else{
			xl.push_back(0);
			b++;
		}//b记录未被禁言的R的个数
	}
	while(a&&b){//反复遍历直到只剩下一个字符
		for(int i=0;i<xl.size();i++){
			if(xl[i]<0){
				continue;
			}//跳过已被禁言的字符
			if(xl[i]){
				if(x){
					a--;
					x--;
					xl[i]=-1;
				}
				else{//增加可禁言次数
					y++;
				}
				
			}
			else{
				if(y){
					b--;
					y--;
					xl[i]=-1;
				}
				else{//同上
					x++;
				}
			}
		}
	}
	if(a){//最后剩下的是D
		cout<<'D';
	}
	else{//反之则是R
		cout<<'R';
	}
	return 0;
} 
```

---

## 作者：听取MLE声一片 (赞：2)

（已经按照基本规范里的逐字逐句查看，请您康康）

这道题还是一道比较好的题目。

### 暴力解法：

思路：每个人要禁言对方最靠前的人。

先用一个 `while` 循环，从头查找有发言权限的人，如果这个人有自由发言权限，则从头找对方能自由发言的人，如果找到，将其禁言。

如果没看懂的话可以看一下这里的代码：

```
for(int i=0;i<n;i++){
		cin>>a[i];//这里是输入，顺便统计一下每个团队的人数。
		if(a[i]=='D')
			ans1++;
		else ans2++;
	}
	while(ans1!=0&&ans2!=0){//任何一个团队能发言的人数清零则退出循环。
		for(int i=0;i<n;i++){
			if(book[i])//如果禁言了返回。
				continue;
			if(a[i]=='D'){
				for(int j=0;j<n;j++){//找到对方最前可发言的人。
					if(a[j]=='D'||book[j])
						continue;
					ans2--;//禁言了一个人。
					book[j]=1;
					break;//直接退出，因为只能禁言一个人。
				} 
			}
			else{
				for(int j=0;j<n;j++){//同理。
					if(a[j]=='R'||book[j])
						continue;
					ans1--;
					book[j]=1;
					break;
				} 
			}
			if(ans1==0||ans2==0)//如果一个团队没人，时间优化。
				break;
		}
	} 
	if(ans1==0)//输出，D 团队没人输出 R ，R 团队没人输出 D。
		cout<<'R';
	else cout<<'D';
```

### 满分解法

还是用一个 `while` 循环，然后从头查找，但后面的不太一样。

先设立两个计数器，统计这个团队出现的数量。如果这一个人是团队 D ，如果团队 R 的计数器不为零，表示前面有一个人可以禁言这个 D 团队人，R 团队这一轮可以禁言的人减少一个，这个D团队人标记被禁言。如果这个人是D团队，则相反。

下面是代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,ans1,ans2,s1,s2,book[200001];//两个计数器。
char a[200001];
int main()
{
	n=read();
	for(int i=0;i<n;i++){
		cin>>a[i];//还是之前的输入。
		if(a[i]=='D')
			ans1++;
		else ans2++;
	}
	while(ans1&&ans2){//同上代码。
		for(int i=0;i<n;i++){//枚举每个人。
			if(book[i])//被禁言了
				continue;
			if(a[i]=='D'){//如果有一个 D 团队的人。
				if(s2){//R团队有人禁言这个人。
					s2--;
					ans1--;
					book[i]=1;//这个人被禁言。
				}
				else s1++;
			}
			else{//同理。
				if(s1){
					s1--;
					ans2--;
					book[i]=1;
				}
				else s2++;
			}
			if(!ans1||!ans2)//判断有没有一个团队没有人，时间优化。
				break;
		}
	}
	if(ans1==0)
		cout<<'R';
	else cout<<'D'; 
	return 0;
}

```

谢谢大家！


---

## 作者：AlicX (赞：1)

## Solution 

通过直觉感觉这个东西是暴力，那么证明一下时间复杂度即可。考虑 `D` 一定会禁言一个 `R`，`R` 同理，所以如果暴力去模拟的话每个人只会被禁言一次，而当 `D` 或者 `R` 的数量为 $0$ 时便可以结束，一轮至少淘汰 $\left\lfloor\dfrac{2}{x}\right\rfloor$ 个人，$x$ 为当前这一轮的人数，所以最坏会进行 $\log n$ 轮，所以最坏时间复杂度为 $O(n \log n)$。

注意特判 `D` 或者 `R` 数量为 $0$ 的情况。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=3e5+10; 
int n; 
int a[N]; 
bool st[N]; 
signed main(){  
    scanf("%d",&n); char c; int cnt1=0,cnt2=0; int num1=0,num2=0;   
    for(int i=1;i<=n;i++) cin>>c,a[i]=(c=='D'),cnt1+=(a[i]==1),cnt2+=(!a[i]); 
    if(!cnt1){ puts("R"); return 0; } if(!cnt2){ puts("D"); return 0; } 
    int T=log2(n); while(T--){  
        for(int i=1;i<=n;i++){ 
            if(st[i]) continue; 
            if(a[i]){ 
                if(num2){ 
                    st[i]=true,num2--; 
                    continue; 
                } cnt2--,num1++; 
            } else{ 
                if(num1){
                    st[i]=true,num1--; 
                    continue; 
                } cnt1--,num2++; 
            } if(!cnt1){ 
                puts("R"); 
                return 0; 
            } if(!cnt2){ 
                puts("D"); 
                return 0; 
            } 
        } 
    } return 0; 
} 
```




---

## 作者：_Winham_ (赞：1)

题目意思：

有两个团队的人在一起玩游戏。每次一个人发言，而那个人可以选择一个对面团队的人出局。题目想要你知道最后剩下的人是哪个团队的。

---

思路：

没什么难的，用队列去存两个团队的人的号码。现在让每个发言的人选择离自己最近的对手禁言。不过在模拟的过程中我们可以直接比较现在活着的人的两个团队最早发言人的编号，小的则就活下来，因为小的要选择对面禁言。而活下来的编号则会变成新的一轮的编号，为 当前编号 $+ n$。


代码实现：

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<cstdio>
#include<queue>
#include<stack>
#include<deque>
using namespace std;
#define int long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
string s;
int n,a,b; 
queue<int>d,r;
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n>>s;
	for(int i=0;i<n;i++)
		(s[i]=='D')?d.push(i):r.push(i);
	while(!d.empty()&&!r.empty()){
		a=d.front(),b=r.front();
		d.pop();r.pop();
		if(a>b)r.push(b+n);
		else d.push(a+n);
	}
	cout<<((!d.empty())?"D":"R")<<endl;
	return 0;
}

```

---

## 作者：Xdl_rp (赞：1)

就直接模拟。

- 定义一个结构体，`nm` 表示所在的队列，`flag` 表示是否被禁言，每一次都继续模拟，如果还有 `D` 能发言，那么禁言 `R` 的人就会加一，反之有 `R` 能发言，就禁言一个 `D`，一直这样模拟下去，直到某一队全部人都被禁言了，就结束了，需执行 $\lceil(\sqrt{n ^ 2})\rceil$ 次。

```cpp
	int ctd = 0, ctr = 0, cnt = 0;//有多少D被禁言了，有多少R被禁言了，总共禁言了多少人
	for (int i = 1; i <= n; i++) {
		if (a[i].flag == 1) continue;//如果被禁言了，就不进行下去
		if (a[i].nm == 'D') {//如果为D
			if (ctd > 0) ctd--, a[i].flag = 1, cnt++;//禁言D的减一，标记禁言，总数加一
			else ctr++;//不然就禁言一个R
		}
		if (a[i].nm == 'R') {//如果为R
			if (ctr > 0) ctr--, a[i].flag = 1;//与上同
			else ctd++;
		}
		if (cnt == n - 1){//如果禁言了 n - 1 人，就只剩一个人了
			f = 1;//标记退出
			break;//退出
		}
	}
```
但是会一直循环下去，所以需要在外面套一个循环，因为每一次最少会禁言剩下一半的人，所以只需要模拟 $\lceil(\sqrt{n ^ 2})\rceil$ 次即可，注意那个 `flag` 变量一定要赋值为 $0$！不然会系统自动生成，~~但是定义在局部变量好像不会~~。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct node {
	char nm;
	bool flag;
	node(): flag(0) {}//初始化
}a[N];
int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].nm;
	}
    //下面不做过多解释，上面已解释过
	int ctd = 0, ctr = 0, cnt = 0;
	for (int j = 1; j <= ceil((double)sqrt(n)); j++) {
	    bool f = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i].flag == 1) continue;
			if (a[i].nm == 'D') {
				if (ctd > 0) ctd--, a[i].flag = 1, cnt++;
				else ctr++;
			}
			if (a[i].nm == 'R') {
				if (ctr > 0) ctr--, a[i].flag = 1;
				else ctd++;
			}
			if (cnt == n - 1){
				f = 1;
				break;
			}
		}
		if (f == 1) break;
	}
	for (int i = 1; i <= n; i++) {
		if (a[i].flag != 1) {
			cout << a[i].nm << endl;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：李至擎 (赞：1)

[点我看题](https://www.luogu.com.cn/problem/CF749C)

一道很好的题目，既能锻炼思维，代码也很简单。

思路：

- $1.$ 先看一下不禁言时的发言顺序：每个人发言完毕后，回到队尾等待下一次的发言——很明显地看出，这是一个先进先出的循环。那么，我们就发现了，可以用队列来模拟这一过程；

- $2.$ 再来看看禁言——为了给自己的党派创造机会，每个人必定会对另一个党派的发言人使用禁言机会。那么，这道题的方法就很明显了。

方法（以一轮发言为例）：

- $1.$ 对于每次发言，取出队顶的人；

- $2.$ 根据那个人的党派去禁言另一个党派的一个人；

- $3.$ 将此人压进队列，等候下一次发言。

细节：

- 一个党派的人都被禁言时，另一个党派可能不止一个人。所以不能用单纯用总人数来判断是否结束，必须记录下两派的人数。 

PS：具体实现方法——禁言：

在上文的方法中，如果要禁言一个人时，我们要顺着发言队列找到下一个非我族类，并禁言他。但是，我们发现用队列进行模拟时，这种操作是无法做到的。那么，有什么代替的解决办法吗？答案是肯定的。

我们可以另外用两个变量将两派的禁言次数储存下来，然后在处理到一个人时，假如他的对手还有禁言次数没用，那么他将被禁言；反之，他的党派也获得一次禁言机会，并将这个幸运儿重新排入下一轮的发言队列——这样做，与前文的方法的效果是一样的。

代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
char opt;//opt是输入字符时的工具 
queue<char>q;//q是用来储存当前发言队列的 
int d,r,n,D,R;//d和r是当前两党各剩下多少个能发言的人，n是初始总人数，D和R是当前两党各还有多少次禁言机会 
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>opt;//输入 
		q.push(opt);//加入发言队列 
		if(opt=='D')d++;//如果是D党，则D党人数+1 
		else r++;//如果是R党，则R党人数+1 	
	}
	while(d&&r)//如果两党都还有剩下的人（还能打起来） 
	{
		char p=q.front();//p是当前发言人 
		q.pop();//用了这次发言机会 
		if(p=='D')//如果此人是D党
		{
			if(R)d--,R--;//如果此时R党还有禁言次数没用，则用掉此次禁言机会，禁言这个D党的人 
			else D++,q.push(p);//反之，则D党获得并保留一次机会，同时将此人加入下一轮发言队列 
		}
		else//如果此人是R党 
		{
			if(D)D--,r--;//如果此时D党还有禁言次数没用，则用掉此次禁言机会，禁言这个R党的人
			else R++,q.push(p);//反之，则R党获得并保留一次机会，同时将此人加入下一轮发言队列 
		}
	}
	if(d)cout<<"D";//如果最后剩下的人是D党，则D党获胜 
	else cout<<"R";//反之，则R党获胜  
	return 0;//结束程序 
}
```

---

## 作者：封禁用户 (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf749c-voting/)
## 题目大意

给定一个字符串，字符串中字符为 $\texttt{D}$ 或 $\texttt{R}$，代表两个团队。从 $1$ 开始，每个人都有发言的权利，发言时，可以禁言一个人，使那个人以后都不能发言。

如果一圈发言完还有 $1$ 个以上的人能发言，就从 $1$ 重新开始，直到只有 $1$ 个人能发言，那个人所在的团队获胜。

## 思路
当一个人发言时，他应该将另外一队在他后面发言中最靠近他的人禁言。

因为一旦另外一队的人被禁言了一个，那么我们这一队可以发言的人就多了一个。如果禁言的人离正在发言的人很远，那么在紧挨着他的那个人就有机会将正在发言的人那一队的人禁言。而如果将距自己最近的人禁言了，那么自己之后的队友就可以发言并发将将后面的对方的人禁言的了。

因为在发言时就模拟将对方禁言过于复杂，我们其实可以直接记录双方禁言对方的数量。

如果对方禁言己方的数量大于 $0$ 就说明自己被禁言了，将对方禁言的数量减 $1$，将自己标记为被禁言。反之说明对方并未将你禁言，将己方禁言对方的数量加 $1$。

## AC Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,s1,s2,cnt;
bool vis[N];
char a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>a+1;
	while(cnt<=n){
		for(int i=1;i<=n;i++){
			if(vis[i]) continue;
			if(a[i]=='D'){
				if(s2>0) s2--,vis[i]=1;
				else s1++,cnt++;
			}
			else{
				if(s1>0) vis[i]=1,s1--;
				else s2++,cnt++;
			}
		}
	}
	if(s1>s2) cout<<'D';
	else cout<<'R';
	return 0;
}
```

---

## 作者：int_stl (赞：0)

一道小清新思维题。

考虑使用两个队列分别维护 $R$ 团队和 $D$ 团队的成员的发言时间。

对于每次操作：

- 把 R 和 D 团队的首个发言人的时间取出来，分别为 $T_D$ 和 $T_R$。

- 如果 $T_D < T_R$，那么说明 $D$ 先发言，那么他可以将 $R$ 目前的第一个发言人禁言，而 $D$ 的发言时间 $T_D \gets T_D + n$，并将 $T_D$ 放入队尾，这样可以避免时间的冲突。

- 对于另一种情况，操作方法见上。

- 如果此时 $D$ 的队列空了，那么 $R$ 赢；如果 $R$ 的队列空了，那么 $D$ 赢；否则继续执行下去。

代码主体部分如下：
```cpp
int v[200006];
queue <int> q[5];
map <char, int> m;
int main() {
	m['D'] = 1, m['R'] = 2;
	int n;
	cin >> n;
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++) q[m[s[i]]].push(i + 1);
	while (1) {
		if (q[1].empty()) {
			cout << 'R';
			return 0;
		}
		if (q[2].empty()) {
			cout << 'D';
			return 0;
		}
		int t1 = q[1].front(), t2 = q[2].front();
		if (t1 < t2) {
			q[2].pop();
			q[1].pop();
			q[1].push(t1 + n);
		}
		else {
			q[1].pop();
			q[2].pop();
			q[2].push(t2 + n);
		}
	}
}
```

---

## 作者：OIerZhang (赞：0)

# [CF749C Voting](https://www.luogu.com.cn/problem/CF749C) 题解

很巧妙的一道~~水~~题。

## 思路

拿到这道题，估计有一些萌新不知道从何处下手，但是如果我们将题目投票的过程模拟一遍，就会发现：“当每一次某人发言之后，这个人等待下一轮”的这个过程就相当于把这个人从队首挪到队尾。

这道题，用队列再合适不过了！

---

### 接下来，我们要思考最优的淘汰方案：

如果自己的一方（假如是 $\texttt{R}$）想要赢，肯定要优先淘汰敌方（也就是 $\texttt{D}$）的人。如果我们淘汰了位置比较靠后的 $\texttt{D}$，那么下一个未被淘汰的 $\texttt{R}$ 就会淘汰我方的人，所以我们又得出：被淘汰的敌方的人越靠前越好（不给对方留机会）。

---

### 可是，新的问题又来了：

如果要淘汰某个人，直接处理很麻烦，毕竟队列只能操作队首和队尾。

但是，我们是要淘汰最靠前的对手的，所以我们可以存两个变量 $\text{pd}$ 和 $\text{pr}$ ，表示 $\texttt{D}$ 方和 $\texttt{R}$ 方有几个敌方的人需要被淘汰（说白了就是每一方有多少“禁言卡”），只要队首为某一方并且敌方有“禁言卡”（$\text{pd}$ 或 $\text{pr}$ 不为 $0$），那么那个人直接弹出队列，永远不再入队。

---

最后，只要判断当其中一方全军覆没时，输出另一方的团队名缩写（$\texttt{D}$ 或 $\texttt{R}$）即可。

## 核心代码

代码里有非常详细的注释，希望你们能看懂~

```cpp
queue <char> q;
string s;
int n, cd = 0, cr = 0, pd = 0, pr = 0; // cd 和 cr 指每方还剩多少人
cin >> n >> s;
for (int i = 0; i < n; i++)
{
    if (s[i] == 'D') // 计算每方有多少人
        cd++;
    else
        cr++;
    q.push(s[i]); // 入队
}
while (cd && cr)
{
    char cur = q.front(); // 取出队首
    q.pop();
    if (cur == 'D') // 如果是 D 方
    {
        if (pr > 0) // 如果对方有禁言卡
            cd--, pr--; // 直接淘汰，耗费对方一张禁言卡
        else // 对方没有禁言卡了！
        {
            pd++; // 给己方贡献一个淘汰对方的名额
            q.push(cur); // 站到队尾
        }
    }
    else // 和上面同理
    {
        if (pd > 0)
            cr--, pd--;
        else
        {
            pr++;
            q.push(cur);
        }
    }
}
if (cd) // D 方还有人
    cout << 'D';
else // R 方没有人
    cout << 'R';
// 由于while循环的条件是当双方都还有人时执行，所以如果循环结束，一定有一方的人都被淘汰。
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

现在有 $n$ 个人围着桌子。第一次会从第一个人开始，通过以下规则操作：

1. 当前发言的人可以淘汰一个敌方的人。

2. 被淘汰的人**不能**发言。

3. 第 $n$ 个人发言结束后，是第 $1$ 个人发言。

最后，会剩下一个队伍的人，而另一个队的人则会全部被淘汰。请你输出这个**剩下**的队伍。

### 分析

因为第 $n$ 个人发言完，就又回到了第 $1$ 个人发言。因此，可以将其理解为 $1$ 号在发言结束后排到了 $n$ 号的后面。这样就可以看出这其实就是队列，从队头进行发言，发言完后又排到队尾。

每个人发言时可以淘汰一个敌方的人。但是我们不知道他淘汰谁最好。如果不把敌人淘汰敌人就会淘汰我们，所以我们只需要将淘汰一个人看成**多了一次**淘汰别人的机会。之后，只要出现了敌方发言，如果有机会就将他淘汰，没有就让他所在的队伍淘汰机会加一。就类似发言的人可以知道淘汰谁是最有利的。

每次淘汰的时候，对那个队伍的人数减一。如果减到了 $0$，那么就输出另外一个队。

对以上思路整理一下，就可以很容易的写出代码了。

### 代码

```
#include <iostream>
#include <cstdio>
#include <queue>
const int N = 2e5 + 10;
using namespace std; 
int n;
string s;
queue<char> p;//存接下来发言的人 
int dc, rc;
int dh, rh;
//dh:teamD's human
//rh:teamR's human
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		char c;
		cin >> c;
		p.push(c); 
		if(c == 'D') dh++;
		if(c == 'R') rh++;
		//记录下每个队的人数 
	}
	while(dh && rh)//两个队还有人可以继续吵架 
	{
		char now = p.front();
		if(now == 'D')//下一个发言的人是D队的 
		{
			if(rc)
			{
				rc--;//用了一次淘汰的机会 
				p.pop();
				dh--;//被淘汰 
			}
			else
			{
				dc++;//可以淘汰一个人 
				p.push(now);//回到队尾等待下次发言  
				p.pop();
			}
		}
		if(now == 'R')//如上 
		{
			if(dc)
			{
				dc--;
				p.pop();
				rh--;
			}
			else
			{
				rc++;
				p.push(now);
				p.pop();
			}
		}
	}
	cout << p.front() << endl;
	//输出下一个发言的人的所在队，因为他还能发言，所以这支队伍一定存在 
	return 0;
}
```

---

## 作者：泠小毒 (赞：0)

# Voting
给定一个字符串，字符串中字符为D或R，代表两个团队

从1开始，每个人都有发言的权利，发言时，可以禁言一个人，使那个人以后都不能发言

如果一圈发言完还有1个以上的人能发言，就从1重新开始，直到只有1个人能发言，那个人所在的团队获胜
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190508/)
## 解法
可以挂个链表，然后头尾连起来，可以一直扫，结束条件可以优化，当场上只有一个团队时结束

因为最优策略是将另一个团队后一个发言的人禁言，所以每次扫到一个人，看是否被禁言，如果被禁言了，在链表中删去这个点

这样做的复杂度是nlogn的，因为每次会禁言一半
## ac代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n,nw,s[200010],l[200010],r[200010],cnta,cntb,lena,lenb,dela,delb;
char ch;
int main()
{
    scanf("%d",&n),getchar();
    for(register int i=1;i<=n;++i)
    {
        scanf("%c",&ch),l[i]=i-1,r[i]=i+1;
        if(ch=='D')s[i]=1,cnta++;else s[i]=2,cntb++;
    }
    l[1]=n,r[n]=1,nw=1;
    while(cnta!=lena&&cntb!=lenb)
    {
        if(s[nw]==1)
        {
            if(dela)r[l[nw]]=r[nw],l[r[nw]]=l[nw],dela--;
            else delb++,lenb++;
        }
        if(s[nw]==2)
        {
            if(delb)r[l[nw]]=r[nw],l[r[nw]]=l[nw],delb--;
            else dela++,lena++;
        }
        nw=r[nw];
    }
    if(cnta==lena)puts("R");else puts("D");
    return 0;
}
```

---

