# [GCJ 2014 Qualification] Magic Trick

## 题目背景

**注意：** 要晋级下一轮，你需要获得 25 分。仅解决本题无法获得足够的分数。


## 题目描述

最近你去看了一场魔术表演。你对其中的一个戏法印象深刻，因此你决定尝试揭开其中的秘密！

魔术师首先将 $16$ 张牌摆成一个正方形：共 $4$ 行，每行 $4$ 张牌。每张牌正面都写有 $1$ 到 $16$ 中的一个不同的数字。接着，魔术师请一位观众选择一张牌，并告诉他这张牌所在的行号。

然后，魔术师可能以不同的顺序再次将 $16$ 张牌摆成一个正方形。魔术师再次询问观众她的牌现在在第几行。仅凭观众对这两个问题的回答，魔术师就能准确地说出观众选的是哪张牌。不可思议，对吧？

你决定写一个程序来帮助你理解魔术师的技巧。程序将获得两次牌面布局，以及观众对于两个问题的回答：第一次布局所选牌的行号，以及第二次布局所选牌的行号。行号从上到下编号为 $1$ 到 $4$。

你的程序应当判断观众选的是哪张牌；或者如果有多种可能的牌（即魔术师失误），输出“Bad magician!”；或者如果没有任何牌符合观众的答案（即观众作弊），输出“Volunteer cheated!”。


## 说明/提示

**数据范围（6 分）**

- $1 \leq T \leq 100$。
- $1 \leq$ 两次回答 $\leq 4$。
- $1$ 到 $16$ 的每个数字在每次布局中恰好出现一次。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
3
2
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
3
1 2 5 4
3 11 6 15
9 10 7 12
13 14 8 16
2
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
2
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
2
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
3
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16```

### 输出

```
Case #1: 7
Case #2: Bad magician!
Case #3: Volunteer cheated!```

# 题解

## 作者：qkj_qwq (赞：3)

## 解题思路
模拟。

先把第一个回答中的那一行用 `map` 记录下来，再在第二个回答中，若有数字被第一个回答的 `map` 记录过，则 $s\gets s+1$，再记录当前数字。然后分类讨论：

- 若 $s=1$，直接输出记录的数字；
- 若 $s=0$，没有任何牌符合观众的答案，输出 `Volunteer cheated!`；
- 若 $s>1$，有多种可能的牌，输出 `Bad magician!`。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,bool>p;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		p.clear();
		int n,m,s=0,t;
		cin>>n;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
			{
				int x;
				cin>>x;
				if(n==i)p[x]=1;
			}
		cin>>m;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
			{
				int x;
				cin>>x;
				if(m==i&&q[x])s++,t=x;
			}
		if(s==1)cout<<t<<'\n';
		else if(!s)cout<<"Volunteer cheated!\n";
		else cout<<"Bad magician!\n";
	}
	return 0;
}
```

---

## 作者：lizongrui000 (赞：3)

### 分析题目
$T$ 组数据，每组数据都有两个答案和两个 $4 \times 4$ 的矩阵，两个答案表示其对应矩阵的行，看这两行的数据中相同的数据有几个。  
+ 如果没有，就输出观众作弊对应的英文。  
+ 有一个，就输出这个数。  
+ 大于一个，就输出魔术师失误对应的英文。
### 代码思路
先输入 $T$，边输入边输出。先输入 $ans1$，表示第一个答案，再输入第一个 $4 \times 4$ 的矩阵，用一个数组 $c$ 存储 $ans1$ 行的数据。  
再输入 $ans2$, 输入第二个矩阵，用数组 $d$ 存储。

```cpp
cin>>ans1;
for(int i=1;i<=4;++i)
{
    for(int j=1;j<=4;++j)
    {
        cin>>a;//因为输入矩阵后只存储行，矩阵不会用到了，所以不用定义二维数组。
        if(i==ans1)
        {
        c[j]=a;
        }
    }
}
cin>>ans2;
for(int i=1;i<=4;++i)
{
    for(int j=1;j<=4;++j)
    {
        cin>>a;
        if(i==ans2)
        {
            d[j]=a;
        }
    }
}
```
现在我们获取了在矩阵变换前后观众选的这个数分别所在的行，接着要写两个循环套在一起，判断这两行中相同的数的个数。
```cpp
cout<<"Case #"<<y<<": ";//提前输出确定输出的内容
int s=0;
for(int i=1;i<=4;++i)
{
    for(int j=1;j<=4;++j)
    {
        if(c[i]==d[j])
        {
            s++;//相同计数器就加1
        }
    }
}
```
接着判断相同的数有几个。输出什么开头已经说了，主要是该怎么输出观众选的这个数。因此在判断 $s = 0$ 后再写两个循环套在一起，如果相同就输出。
```cpp
if(s==0) cout<<"Volunteer cheated!"<<endl;//观众作弊情况
else if(s==1)
{
    for(int i=1;i<=4;++i)
    {
        for(int j=1;j<=4;++j)
        {
            if(c[i]==d[j])
            {
                cout<<c[i]<<endl;//找到这个数后就输出
            }
        }
    }
}
else if(s>=2) cout<<"Bad magician!"<<endl;//魔术师失误情况
```
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,ans1,ans2;
int a,c[10],d[10];
int main()
{
	cin>>t;
	for(int y=1;y<=t;++y)
	{
		cin>>ans1;
		for(int i=1;i<=4;++i)
		{
			for(int j=1;j<=4;++j)
			{
				cin>>a;
				if(i==ans1)
				{
					c[j]=a;
				}
			}
		}
		cin>>ans2;
		for(int i=1;i<=4;++i)
		{
			for(int j=1;j<=4;++j)
			{
				cin>>a;
				if(i==ans2)
				{
					d[j]=a;
				}
			}
		}
		cout<<"Case #"<<y<<": ";
		int s=0; 
		for(int i=1;i<=4;++i)
		{
			for(int j=1;j<=4;++j)
			{
				if(c[i]==d[j])
				{
					s++;
				}
			}
		}
		if(s==0) cout<<"Volunteer cheated!"<<endl;
		else if(s==1)
		{
			for(int i=1;i<=4;++i)
			{
				for(int j=1;j<=4;++j)
				{
					if(c[i]==d[j])
					{
						cout<<c[i]<<endl;
					}
				}
			}
		}
		else if(s>=2) cout<<"Bad magician!"<<endl;
	}
	return 0;
}
```

---

## 作者：__F__ (赞：2)

## 题目大意  
给定两个由 $16$ 个数字组成的 $4\times 4$ 的数字正方形，并给出两次提问的答案，分别对应第一个数字正方形的某一行和第二个数字正方行的某一行，查找这两行中有没有重复的数字。如果有一个重复的数字，输出这个数字；如果有多个重复的数字，输出 `Bad magician!`；如果没有重复的数字，输出 `Volunteer cheated!`。  
## 思路分析  
根据题意模拟即可。先输入提问的答案（也就是哪一行），再输入数字正方形，把提问的那一行的数存到一个数组里，第二个数字正方形也做相同的处理，最后看两个单独存储某一行数字的数组有无重复的数字，分情况输出即可。  
## [AC](https://www.luogu.com.cn/record/224024494) code  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace FastIO{
    const int sz=1<<20;
    char inbuf[sz],outbuf[sz];
    int il=0,ir=0;
    int outr=0;
    inline void load(){
    	int len=fread(inbuf,1,sz,stdin);
    	il=0;
    	ir=len;
	}
	inline char getchar(){
		if(il>=ir) load();
		if(il>=ir) return EOF;
		return inbuf[il++];
	}
	inline int read(){
		int x=0,f=1;
		char ch=getchar();
		while(ch<'0'||ch>'9'){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while(ch>='0'&&ch<='9'){
			x=x*10+(ch-'0');
			ch=getchar();
		}
		return x*f;
	}
	inline void flush(){
		fwrite(outbuf,1,outr,stdout);
		outr=0;
	}
	inline void putchar(char ch){
		outbuf[outr++]=ch;
		if(outr==sz) flush();
	}
	inline void write(int x){
		if(x<0){
			putchar('-');
			x=-x;
		}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	struct Flusher{
		~Flusher(){ flush(); }
	}flusher;
}
using FastIO::read;
using FastIO::write;
using FastIO::putchar;
int  T;
signed main(){
	ios::sync_with_stdio(0);
	cout.tie(0);
	T=FastIO::read();
	for(int t=1;t<=T;t++){
		int first,second;//first,second分别存储两次提问的结果 
		int f[10][10],s[10][10];
		first=FastIO::read();
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				f[i][j]=FastIO::read();
			}
		}
		int f1[10];//f1存储第一个数字正方形被提问的那一行的数 
		for(int j=1;j<=4;j++){
			f1[j]=f[first][j];
		}
		second=FastIO::read();
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				s[i][j]=FastIO::read();
			}
		}
		int s1[10];//s1存储第二个数字正方形被提问的那一行的数  
		for(int j=1;j<=4;j++){
			s1[j]=s[second][j];
		}
		int count=0;//count存储相同数字的个数 
		int index;//index存储出现相同数字的下标位置 
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				if(f1[i]==s1[j]){
					count++;
					index=i;
				}
			}
		}
		if(count==1) cout<<"Case #"<<t<<": "<<f1[index]<<"\n";//对count进行分类讨论，按题意输出即可 
		else if(count>1) cout<<"Case #"<<t<<": Bad magician!"<<"\n";
		else if(count==0) cout<<"Case #"<<t<<": Volunteer cheated!"<<"\n";
	}
}
```

---

## 作者：_hud (赞：1)

# 题解：[P13243 \[GCJ 2014 Qualification\] Magic Trick](https://luogu.com.cn/problem/P13243)

## 思路

模拟。

由题意，我们只需找到第一次布局中所选牌所在的行与第二次布局中所选牌所在的行中找出重复的的牌即可。若重复的牌数：

- $< 1$，输出 `Volunteer cheated!`；
- $= 1$，输出该牌上的数字；
- $> 1$，输出 `Bad magician!`。

讲完思路再来讲讲实现。在输入时只需记录我们需要的这两行，前者用数组存储，后者用桶存储，然后逐一判断即可。具体可以看代码。

注意：多测清空！

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[5], n, m;
bool f[17]; // 桶
inline void sol() {
    memset(f, 0, sizeof f); // 多测清空
    cin >> n; int tmp;
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 4; ++j)
            // 只输入第一次布局中所选牌所在的行
            if(i == n) cin >> a[j]; // 用数组存储
            else cin >> tmp;
    cin >> m;
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 4; ++j)
            // 只输入第二次布局中所选牌所在的行
            if(i == m) cin >> tmp, f[tmp] = 1; // 用桶存储
            else cin >> tmp;
    tmp = 0; // 用来存储重复的数，没有即为 0
    for(int i = 1; i <= 4; ++i)
        if(f[a[i]]) { // 逐一判断是否重复
            if(tmp) { cout << "Bad magician!\n"; return; }
            tmp = a[i];
        }
    if(tmp) cout << tmp << '\n';
    else cout << "Volunteer cheated!\n";
}
signed main() {
    cout.tie(0), cin.tie(0) -> sync_with_stdio(0);
    int T; cin >> T;
    for(int _ = 1; _ <= T; ++_) {
        cout << "Case #" << _ << ": ";
        sol();
    }
    return 0;
}
```

---

## 作者：Xjj2013_0405 (赞：1)

## 思路 ##
这是一到极其简单的模拟题。
先将观众第一次的回答记下，之后在输入时用数组记录那一行的数，然后记录第二次的答案，在之后的输入中特判那一行，枚举第一次输入时记录的数组，如果有和特判那一行中一样的数，就把答案数量增加 1，并记录答案，最后在输出时判断如果答案就一个，就直接输出，如果不止一个，输出 `Bad magician!`，如果没有答案，输出 `Volunteer cheated!`。
## 代码 ##
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//个人习惯，防RE 
int n,temp1[5],answer;
signed main(){
	cin >> n;
	for(int t = 1;t <= n;k++) 
	{
		int ans = 0,root;//记录答案数量和答案 
		memset(temp1 , 0 , sizeof(temp1));//多测清空 
		cin >> answer;//记录观众第一次回答
		for(int i = 1;i <= 4;i++)
		{
			for(int j = 1;j <= 4;j++)
			{
				int num;//应付输入 
				cin >> num;
				if(i == answer)//记录观众第一次回答的行数的数
				{ 
					temp1[j] = num;
				}
			}
		} 
		cin >> answer;//记录观众第二次回答 
		for(int i = 1;i <= 4;i++)
		{
			for(int j = 1;j <= 4;j++)
			{
				int num;
				cin >> num;
				if(i == answer)// 判断答案 
				{
					for(int k = 1;k<=4;k++)
					{
						if(num==temp1[k])
						{
							ans++;//找到的话就加1 
							root=num;//记录答案 
						}
					}
				}
			}
		} 
		cout << "Case #" << k << ": ";//格式 (注意空格)
		if(ans==1)//答案就1个，直接输出 
		{
			cout << root << "\n";
		}
		else if(ans>1)//答案不止一个 
		{
			cout << "Bad magician!\n";
		}
		else if(ans==0)//没答案 
		{
			cout << "Volunteer cheated!\n";
		}
	}
	return 0;//完结撒花 
}
```

---

## 作者：qwq_Furry (赞：1)

## 解题思路
### 第一步
 - 我们先设置好变量 $T$，代表有多少组测试数据；然后设置变量 $pri$，用于输出第 $pri$ 个数据。

### 第二步
 - 进入循环里面，创建一个目标行数 $tn_1$，还有需要输入的数组 $poker1$ 以及后面需要用到的数组 $ans_1$，然后输入的时候判断（后面所有的 $i$ 表示行数，$j$ 表示列数），将会有 $2$ 种情况：
   - 如果 $i = tn_1$，那么先输入 $poker1_{i,j}$，然后让 $ans1_j = poker1_{i,j}$ 就行。

   - 如果 $i \not= tn_1$，那么直接输入 $poker1_{i,j}$ 即可。
  
 - 接下来会继续输入一些数字，也是同样的，创建目标行数 $tn_2$，还有要输入的数组 $poker2$ 以及后面要用的数组 $ans_2$。也是会有 $2$ 种情况：

   - 如果 $i = tn_2$，那么先输入 $poker2_{i,j}$，然后让 $ans2_j = poker2_{i,j}$ 就行。

   - 如果 $i \not= tn_2$，那么直接输入 $poker2_{i,j}$ 即可。
  
### 第三步
 - 创建 $2$ 个变量，$count$ 和 $tn_u$，分别表示符合的数字数量以及符合的数字。

 - 然后判断每个 $ans1_i$ 是否等于 $ans2_j$，有 $2$ 种情况：

   - 如果 $ans1_i = ans2_j$，那么 $count$ 就加上 $1$，然后 $tn_u = ans1_i$ 或者是 $tn_u = ans2_j$。

   - 如果 $ans1_i \not= ans2_j$，那么直接跳过。
  
### 第四步
 - 判断 $count$ 的数值，有以下 $3$ 种情况：
 
   - 如果 $count = 0$，就是没有任何的数字相同，直接输出 Volunteer cheated!，同时也要将 $pri$ 加上 $1$。

   - 如果 $count = 1$，也就是正好有且只有 $1$ 个数字相同，直接输出 $tn_u$，同时也要将 $pri$ 加上 $1$。
  
   - 如果 $count > 1$，就是有多个数字相同，直接输出 Bad magician!，也要将 $pri$ 加上 $1$ 。
  
## 时间复杂度及空间复杂度分析
按照此思路来写的话，时间复杂度是 $O(T)$，题目限制是 $1 \le T \le 100$，可以通过此题目。

空间复杂度是 $O(1)$，题目限制是 $1.00$ GB，可以通过此题目。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int T, pri = 1; cin >>T;
    while(T--) {
        int tn_1, poker1[6][6], ans1[6]; //tn_1 = target_number_1
        cin >>tn_1;
        for(int i = 1; i <= 4; i++) { //思路里面的第二步
            for(int j = 1; j <= 4; j++) {
                cin >>poker1[i][j];
                if(i == tn_1) ans1[j] = poker1[i][j];
            }
        }
        int tn_2, poker2[6][6], ans2[6]; //tn_2 = target_number_2
        cin >>tn_2;
        for(int i = 1; i <= 4; i++) {
            for(int j = 1; j <= 4; j++) {
                cin >>poker2[i][j];
                if(i == tn_2) ans2[j] = poker2[i][j];
            }
        }
        int count = 0, tn_u;
        for(int i = 1; i <= 4; i++) { //思路第三步
            for(int j = 1; j <= 4; j++) {
                if(ans1[i] == ans2[j]) { //不要加i == j就continue，然后有些就计算不到，导致WA
                    tn_u = ans1[i];
                    count++;
                }
            }
        }
        if(count == 0) cout <<"Case #" <<pri <<": " <<"Volunteer cheated! \n"; //输出
        else if(count == 1) cout <<"Case #" <<pri <<": " <<tn_u <<" \n";
        else if(count > 1) cout <<"Case #" <<pri <<": " <<"Bad magician! \n";
        pri++;
    }
    return 0;
}
```

---

## 作者：Finner_forgeter (赞：1)

# P13243题解

~~这是一道非常费手的题。~~

**思路：**  按照给出的行号存储每一行的数据，若这两行有且只有 $1$ 个相同的数时，输出这个数，如果没有相同的数，说明观众作弊了，输出 `Volunteer cheated!` 即可，如果有多个相同的数，那么魔术师就不能找出数了，所以输出 `Bad magician!`。

**代码实现：**  先输入给出的 $16$ 张牌，然后使用两个数组存储，或直接在方阵里求解即可，使用变量 $cnt$ 计算相同数的个数。

下面给出AC代码：

```cpp
#include<bits/stdc++.h>
#define finner_forgeter return
#define love 0
#define Robin ;
using namespace std;
int T;
int main(){
	cin>>T;
	for(int q=1;q<=T;q++){
		int a[5][5],b[5][5],n1,n2,s1[5],s2[5],cnt=0,flag;
		cin>>n1;
		for(int i=1;i<=4;i++)for(int j=1;j<=4;j++)
		cin>>a[i][j];
		cin>>n2;
		for(int i=1;i<=4;i++)for(int j=1;j<=4;j++)
		cin>>b[i][j];
		for(int i=1;i<=4;i++)s1[i]=a[n1][i];//分别存储两个方阵中所给行的数据 
		for(int i=1;i<=4;i++)s2[i]=b[n2][i];
		for(int i=1;i<=4;i++)for(int j=1;j<=4;j++)
		if(s1[i]==s2[j])cnt++,flag=s1[i];// cnt存储相同数据的个数 
		if(cnt==1){
			cout<<"Case #"<<q<<": "<<flag<<endl;
		}else if(cnt==0){
			cout<<"Case #"<<q<<": Volunteer cheated!"<<endl;
		}else{
			cout<<"Case #"<<q<<": Bad magician!"<<endl;
		}
	}
	finner_forgeter love Robin
}
```

事实上，可以免去存储数组的使用，直接在方阵内求解。可自行探索。

---

## 作者：Zjb13927701829 (赞：1)

# P13243 Magic Trick 题解
[题目传送门](https://www.luogu.com.cn/problem/P13243)
## 读题目：
题目给我们2个正整数 $n,m$ 和2个 $4 \times 4$ 的矩阵 $a,b$。且 $a\text{和}b$ 都是 $1 \sim 16$ 的排列。题目告诉我们有一个数 $x$ 在矩阵 $a$ 的第 $n$ 行、在矩阵 $b$ 的第 $m$ 行，让我们求出这个数。
## 思考做法：
我们仅需要 $a$ 矩阵的第 $n$ 行和 $b$ 矩阵的第 $m$ 行，将他们进行对比：

```cpp
if(i==m){ 
  for(int k=1;k<=4;k++){
    if(x==a[k]) cnt++,d=x;
  }
}
```

用一个计数器 $cnt$ 统计 $x$ 的出现次数，方便判断错误；变量 $d$ 用来保存答案。最后就能将其输出了。
## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    for(int cn=1;cn<=t;cn++){ 
        int n,m,a[5],x,cnt=0,d=0;
        // 节省内存，定义临时变量x
        cin>>n;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                cin>>x;
                if(i==n) a[j]=x;
            }
        }
        cin>>m;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                cin>>x;
                if(i==m){ // 查询
                    for(int k=1;k<=4;k++){
                        if(x==a[k]) cnt++,d=x;
                    }
                }
            }
        }
        cout<<"Case #"<<cn<<": "; // 输出数据
        if(cnt==0){
            cout<<"Volunteer cheated!\n";
        }
        else if(cnt>1){
            cout<<"Bad magician!\n";
        }
        else cout<<d<<endl;
    }
    return 0;
}//完结撒花
```
`审核题解不易，管理员辛苦了！`

---

## 作者：Hkb150429 (赞：0)

## 题意

应当判断观众选的是哪张牌；或者如果有多种可能的牌（即魔术师失误），输出`Bad magician!`；或者如果没有任何牌符合观众的答案（即观众作弊），输出`Volunteer cheated!`。

## 思路

我们把第一个数阵中的第 $n$ 行存下来，第二个数阵的第 $m$ 行存下来，在判断是否有重复，会出现以下 $3$ 种情况：

- 没有一个重复，则输出`Volunteer cheated!`。
- 有多个重复，则输出`Bad magician!`。
- 一个重复，输出答案。
## AC code

```cpp
//管理员大佬审核不易，辛苦啦！求通过QAQ
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int a[10][10],b[10][10];
void scan(){
    cin>>n;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++)cin>>a[i][j];
    }
    cin>>m;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++)cin>>b[i][j];
    }
}
void solve(){
    int c[10],d[10],cnt=0,ans;
    for(int i=1;i<=4;i++)c[i]=a[n][i],d[i]=b[m][i];
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(c[i]==d[j])cnt++,ans=c[i];
        }
    }
    if(cnt==0)cout<<"Volunteer cheated!\n";
    else if(cnt==1)cout<<ans<<"\n";
    else cout<<"Bad magician!\n";
}
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case #"<<i<<": ";
        scan();
        solve();
    }
    return 0;
}

```

---

## 作者：GuoMingXuants1 (赞：0)

### 思路
这道题就是简单数组模拟，虽然题面看上去挺长。

先转化题意，每组测试数据中，给定两个矩阵，并且在这两个矩阵前都指定了一个数，这两个数分别指定的两个矩阵的某一行的所有元素，现在，求这两个行中，有几个重复元素，也就是符合观众选择的牌数，根据牌数的不同，输出不同的文本。如果牌数只有一个，那么就要输出牌上的数字。

用两个数组记录指定的两行即可，再通过遍历查找重复元素。开一个变量，记录重复的元素，这个变量是用来针对只有一个牌数这个情况设计的。

### 代码

```cpp
#include<iostream>
using namespace std;
int a[5][5],b[5][5];
int c[6],d[6];
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n1,n2;
        cin>>n1;
        for(int j=1;j<=4;j++)
        {
            for(int k=1;k<=4;k++)
            {
                cin>>a[j][k];
                if(j == n1)
                {
                    c[k] = a[j][k];
                }
            }
        }
        cin>>n2;
        for(int j=1;j<=4;j++)
        {
            for(int k=1;k<=4;k++)
            {
                cin>>b[j][k];
                if(j == n2)
                {
                    d[k] = b[j][k];
                }
            }
        }
        int cnt = 0;
        int e = 0;
        for(int j=1;j<=4;j++)
        {
            if(d[j] == c[1] || d[j] == c[2] || d[j] == c[3] || d[j] == c[4])
            {
                cnt++;
                e = d[j];
            }
        }
        if(cnt == 0)
        {
            cout<<"Case #"<<i<<": "<<"Volunteer cheated!"<<endl;
        }
        else if(cnt == 1)
        {
            cout<<"Case #"<<i<<": "<<e<<endl;
        }
        else if(cnt>=2)
        {
            cout<<"Case #"<<i<<": "<<"Bad magician!"<<endl;
        }
    }
}
```

---

## 作者：lby_commandBlock (赞：0)

## 思路

简单的模拟。

由题意，将第一次的牌面布局中的第「第一次提问的答案」行的所有数字打标记。随后，枚举所有第二次的牌面布局第「第二次提问的答案」行的所有数字，看看被标记了几个。

- 如果是 $0$ 个：输出 `Volunteer cheated!`；
- 如果是 $1$ 个：输出对应的数字；
- 如果 $\ge 2$ 个：输出 `Bad magician!`。

## 代码

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int N = 50;

int T, ans1, ans2, a1[N][N], a2[N][N];

bool flag[N];

void solve() {
    cin >> ans1;
    for (int i = 1; i <= 16; i++)
        flag[i] = false;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            cin >> a1[i][j];
    cin >> ans2;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            cin >> a2[i][j];
    for (int i = 1; i <= 4; i++)
        flag[a1[ans1][i]] = true;
    int ans = -1;
    for (int i = 1; i <= 4; i++) {
        if (flag[a2[ans2][i]]) {
            if (ans == -1)
                ans = a2[ans2][i];
            else {
                cout << "Bad magician!" << endl;
                return;
            }
        }
    }
    if (ans == -1)
        cout << "Volunteer cheated!" << endl;
    else
        cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    for (int _ = 1; _ <= T; _++) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    return 0;
}
```

---

