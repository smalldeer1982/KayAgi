# The Child and Homework

## 题目描述

Once upon a time a child got a test consisting of multiple-choice questions as homework. A multiple-choice question consists of four choices: A, B, C and D. Each choice has a description, and the child should find out the only one that is correct.

Fortunately the child knows how to solve such complicated test. The child will follow the algorithm:

- If there is some choice whose description at least twice shorter than all other descriptions, or at least twice longer than all other descriptions, then the child thinks the choice is great.
- If there is exactly one great choice then the child chooses it. Otherwise the child chooses C (the child think it is the luckiest choice).

You are given a multiple-choice questions, can you predict child's choose?

## 说明/提示

In the first sample, the first choice has length 39, the second one has length 35, the third one has length 37, and the last one has length 15. The choice D (length 15) is twice shorter than all other choices', so it is great choice. There is no other great choices so the child will choose D.

In the second sample, no choice is great, so the child will choose the luckiest choice C.

In the third sample, the choice B (length 2) is twice longer than all other choices', so it is great choice. There is no other great choices so the child will choose B.

## 样例 #1

### 输入

```
A.VFleaKing_is_the_author_of_this_problem
B.Picks_is_the_author_of_this_problem
C.Picking_is_the_author_of_this_problem
D.Ftiasch_is_cute
```

### 输出

```
D
```

## 样例 #2

### 输入

```
A.ab
B.abcde
C.ab
D.abc
```

### 输出

```
C
```

## 样例 #3

### 输入

```
A.c
B.cc
C.c
D.c
```

### 输出

```
B
```

# 题解

## 作者：封禁用户 (赞：3)

企鹅来写一篇通俗易懂的暴力模拟题解奉上～  
题目传送>>[CF437A](https://www.luogu.com.cn/problem/CF437A)  
### 题意简述：  
一道四选项单选，如一选项描述长度是其他选项的两倍及以上，或其他选项描述长度都是该选项的两倍及以上，则为优秀项，如无优秀项或优秀项不唯一，则一律选 C。  
### 题目分析：  
这难道就是传说中的“三短一长选最长，三长一短选最短，参差不齐 C 无敌......”？其实此题直接据题意暴力模拟已可，主要就是注意一下当优秀项不唯一时需选 C（企鹅就因先未考虑卡在了 #28）。  
### Code:  
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
char a[103], b[103], c[103], d[103];   //开数组存各选项
int judge(int aa, int bb, int cc, int dd)   //写一个函数判断是否为优秀项
{
	if ((aa >= 2 * bb && aa >= 2 * cc && aa >= 2 * dd) || (aa * 2 <= bb && aa * 2 <= cc && aa * 2 <= dd))
	{
		return 1;
	}
	return 0;
}
int main()
{
	 //freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int la, lb, lc, ld;   //定义各选项的描述长度
	gets(a);      //gets 为专门读字符串的函数，读取一行字符串
	gets(b);
	gets(c);
	gets(d);
	la = strlen(a) - 2;   //strlen 计算字符串的长度，需要注意-2，因为选项描述需减去前面的序号和"."
	lb = strlen(b) - 2;
	lc = strlen(c) - 2;
	ld = strlen(d) - 2;
	if (judge(la, lb, lc, ld) && !judge(lb, la, lc, ld) && !judge(lc, la, lb, ld) && !judge(ld, la, lb, lc))   //当且仅当A为优秀项
	{
		cout << "A";
		return 0;
	}
	if (judge(lb, la, lc, ld) && !judge(la, lb, lc, ld) && !judge(lc, la, lb, ld) && !judge(ld, la, lb, lc))   //当且仅当B为优秀项
	{
		cout << "B";
		return 0;
	}
	if (judge(lc, la, lb, ld) && !judge(la, lb, lc, ld) && !judge(lb, la, lc, ld) && !judge(ld, la, lb, lc))   //当且仅当C为优秀项
	{
		cout << "C";
		return 0;
	}
	if (judge(ld, la, lb, lc) && !judge(la, lb, lc, ld) && !judge(lb, la, lc, ld) && !judge(lc, la, lb, ld))   //当且仅当D为优秀项
	{
		cout << "D";
		return 0;
	}
	cout << "C";   //无优秀项或优秀项不唯一
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/3zawfi39.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：dalao_see_me (赞：3)

这蒙题技巧……好像有点厉害的亚子……

# 切入正题

题意：

给出四个字符串，如果某个字符串的长度是其他字符串的长度的两倍及以上，或其他字符串的长度都是这个字符串的两倍及以上，那么这个字符串为备选字符串。

如果有且仅有一个备选字符串，那么输出它的编号（即ABCD）。否则输出C。

既然我们不需要按照字符串的内容来做操作，所以就只要提取一个长度就可以了。

注意一下字符串长度要把前面的两个字符删掉，所以要减二。

然后根据题意模拟即可。
# CODE TIME：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
char P[5]={' ','A','B','C','D'};
int len[5];
int n=4;
vector<int>v;
int main(){
	for(int i=1;i<=n;i++){
		cin>>s;//我们只需要s的长度，并不需要内容，所以只要提取长度即可
		len[i]=s.size()-2;//注意是“描述”的内容，所以提取的长度-2
	}
	for(int i=1;i<=n;i++){
		int f_1=1,f_2=1;//代表两个可能的情况
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			f_1&=(len[i]*2<=len[j]);
			f_2&=(len[i]>=len[j]*2);
		}
		if(f_1|f_2)v.push_back(i);
	}
	if(v.size()!=1)cout<<'C';//不满足要求，输出C 
	else cout<<P[v[0]];
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：1)

先安利一下[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

此题是一个大模拟

当我们在模拟是，可以用两个布尔变量$flag1,flag2$记录此时这个选项两个条件是否满足。

注意在进行模拟时，要把字符串前两个字符（选项和$.$）去掉。否则会WA的很惨

最后再判断有没有两个选项同时满足。如果有，那么就输出C

```cpp
#include <bits/stdc++.h>
using namespace std;
string a[10];
char b[10];//选项
bool c[10];
int main() {
	for (register int i = 1; i <= 4; ++i) {
		getline(cin, a[i]);//读入字符串
		b[i] = a[i][0];
		a[i].erase(0, 2);//string专属函数，删去前两个字符
		//cout << a[i] << endl;
	}
	int cnt = 0;
	for (register int i = 1; i <= 4; ++i) {
		bool flag1 = 1, flag2 = 1;
		for (register int j = 1; j <= 4; ++j) {
			if (j == i) continue;
			if (a[i].size() < a[j].size() * 2) flag1 = 0;
			if (a[i].size() * 2 > a[j].size()) flag2 = 0;//条件不成立 
		}
		c[i] = flag1 | flag2;//有一个成立即可
		//cout << c[i] << endl; 
		cnt += c[i];//优秀选项的个数
	}
	if (cnt == 1) {
		for (register int i = 1; i <= 4; ++i)
			if (c[i]) {
				cout << b[i] <<' ';
				return 0;
			}
	}
	else cout << 'C';
}
```

---

## 作者：LXH5514 (赞：0)

## CF437A The Child and Homework

### 题目大意 

给你四个选项 $A B C D$，每个选项是一个字符串，如果有某一个字符串的长度大于等于其他三串的长度的两倍或小于等于其他三串的长度的一半，那么就选这个选项，否则就选 $C$ 。

### 思路

如果满足上述的那个条件，那么他一定是最长的字符串或者是最短的字符串，因此我们统计最长的长度大于其他 $2$ 倍的串的数量，和最短的长度小于其他 $\frac{1}{2}$ 的数量，如果同时等于 $3$ 或者都小于 $3$ 就选 $C$ ，否则就输出那个选项。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1000000;
int n;
string s[10];
int len[10];
char c[4]={'A','B','C','D'};
int main()
{
	for(int i=1;i<=4;i++)
	{
		cin>>s[i];
		len[i]=s[i].size()-2;//减去A.那些
	}
	int maxn=-1,minx=inf,h1,h2;
	int sum1=0,sum2=0;
	for(int i=1;i<=4;i++)
	{
		if(len[i]>maxn){
			maxn=len[i],h1=i;//记录最大值，并记录选项
		}
		if(minx>len[i])
		{
			minx=len[i];
			h2=i;
		}
	}
	for(int i=1;i<=4;i++)
	{
		if(maxn>=len[i]*2)sum1++;//统计数量
		if(minx<=len[i]/2)sum2++;
	}
	if((sum1==3&&sum2==3)||(sum1<3&&sum2<3))
	{
		printf("C");
		return 0;
	}
	if(sum1==3)
		printf("%c",c[h1-1]);
	if(sum2==3)
	printf("%c",c[h2-1]);	
	return 0;
}
```



---

## 作者：Unordered_OIer (赞：0)

# CF437A 题解
~~每日水题~~

## 题意
如果一个选项的**描述**长度小于其他各项**描述**长度一半，或大于其他各项**描述**长度两倍，则认为这个选项是一个优秀选项。

如果只存在一个优秀选项就输出这个选项，否则输出 $\text C$。

（三短一长选最长，三长一短选最短，不会就选 $\text C$）

## 题解
我们先把各项选项的长度算出来，然后和其他各项逐一比较，每次比较记录当前选项描述的长度和枚举到的选项描述的长度，决定这个选项是否为优秀选项即可。

如果有多个选项特判一下输出 $\text C$ 即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(ll x){write(x),putchar('\n');}
string a,b,c,d; 
int main(){
	cin>>a>>b>>c>>d;
	ll l[5];
	l[1]=a.size()-2,l[2]=b.size()-2;
	l[3]=c.size()-2,l[4]=d.size()-2;
	bool oo[5];
	for(ll i=1;i<=4;i++){
		bool i1=1,i2=1;
		for(ll j=1;j<=4;j++)
			if(i!=j){
				i1&=(l[i]*2<=l[j]);
				i2&=(l[i]>=l[j]*2);
			}
		oo[i]=(i1|i2);
	}
	ll ff=oo[1]+oo[2]+oo[3]+oo[4];
	if(ff!=1)return puts("C"),0;
	else{
		if(oo[1])puts("A");
		if(oo[2])puts("B");
		if(oo[3])puts("C");
		if(oo[4])puts("D");
	}
	return 0;
}
```

---

## 作者：Jr_Zlw (赞：0)

### 一道很好玩的题目

正所谓“三长一短选最短”“三短一长选最长”以及“啥都不是就选C”，这道题目可以帮助我们秒杀英语卷子（不是），只是不知道能蒙对几题呢？ 

### 基本思路

**模拟**

由于这道题目的答案与选项内容无关（奇奇怪怪的），所以只要记录下字符串的长度即可。其次，因为要看“三短一长”或“三长一短”，我们肯定要记下最长的和最短的那个选项。记下$max$和$min$，用$max\div 2$以及$min\times 2$与其他选项进行比较，记下满足条件的数量。如果有满足条件的选项就记录下来， 并且将数量$++$；最后看一下有没有哪一种情况是刚好有$3$个选项满足条件，那么剩下不满足条件的那一个就是我们要求的答案。反之，如果不是有$3$个选项满足要求就肯定只能选“C”了。

那么我们就只要看看两个计数器的值即可，同时要注意去找那个不满足条件的选项（比如可以用一个桶去存储并且查找），最后要特判一下没有 $3$ 以及都是 $3$ 的情况要输出“C”。

### 奉上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int jj1,j2,a1[4],a2[4],mx=-1e9,mi=1e9;
int main()
{
	string s;int a[4];
	for(int i=0;i<=3;++i)
	{
		cin>>s;a[i]=s.length()-2;
		mx=max(mx,a[i]);mi=min(mi,a[i]);
	} 
	for(int i=0;i<=3;++i)
	{
		if(a[i]<=(mx>>1))jj1++,a1[i]=1;
		if(a[i]>=(mi<<1))j2++,a2[i]=1;
	}
	if(jj1>3||j2>3||(jj1==3&&j2==3)) 
	{
		puts("C");return 0;
	}
	if(jj1==3)
	{
		for(int i=0;i<=3;++i)
		if(!a1[i])cout<<char('A'+i);
	} 
	else if(j2==3)
	{
		for(int i=0;i<=3;++i)
	    if(!a2[i])cout<<char('A'+i);
	}
	else puts("C");
	return 0;
}
```


---

## 作者：zilingheimei (赞：0)

蒟蒻又来发题解了（~~然鹅还是水题~~）

首先咱们先看看题目要求：


------------


#### 1如果某个选项的描述的长度是其他选项的描述的长度的两倍及以上

#### 2或者其他选项的描述的长度都是这个选项的两倍及以上那么孩子会认为这个选项是优秀的。

#### 如果有且仅有一个优秀的选项，那么孩子会选择它

#### 否则孩子会选择C


------------


所以在满足1或2的一个条件时，输出这个选项，否则输出c

我们用一个结构体先存下它的选项和长度：


------------

```cpp
for(int i=1;i<=4;i++){
	cin>>s;
	a[i].len=s.size()-2;
	a[i].ans='A'+i-1;
}
```


------------


然后排序
```cpp
sort(a+1,a+1+4,cmp);
```



------------

如果第一是第二的长度两倍及以上或第三是第四的两倍及以上就符合条件

因为排序过了


如果第一>=第二乘以2，第一必定是第三第四的两倍及以上

同理如果第四乘以<=第三，第四的两倍必定小于其他

但在之前必须先判断是不是满足多个条件因为如果同时满足1和2就应该选c

然后如果都不满足也是输出c

所以这段应该这么写


------------

```cpp
if(a[1].len/2>=a[2].len&&a[3].len/2>=a[4].len){
		cout<<"C";
		return 0;
	}
	else if(a[1].len/2>=a[2].len){
		cout<<a[1].ans;
		return 0;
	}
	else if(a[3].len/2>=a[4].len){
		cout<<a[4].ans;
		return 0;
	}
	cout<<"C";
```


------------

注意判断中要加return结束

然后一份ac代码就出来了：


------------


```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
struct cxk{
	int len;
	char ans;
}a[5];
bool cmp(cxk a,cxk b){
	return a.len>b.len;
}
int main(){
	for(int i=1;i<=4;i++){
		cin>>s;
		a[i].len=s.size()-2;
		a[i].ans='A'+i-1;
	}
	sort(a+1,a+1+4,cmp);
	if(a[1].len/2>=a[2].len&&a[3].len/2>=a[4].len){
		cout<<"C";
		return 0;
	}
	else if(a[1].len/2>=a[2].len){
		cout<<a[1].ans;
		return 0;
	}
	else if(a[3].len/2>=a[4].len){
		cout<<a[4].ans;
		return 0;
	}
	cout<<"C";
	return 0;
}
```


---

## 作者：BMMULLER (赞：0)

# 结构体+sort排序

### 1.建立结构体

结构体中包含三个变量，即选项（字符串类型），选项长度（int即可），以及选项名A,B,C,D（char类型）

### 2.进行输入并计算长度

可采用循环，也可以一次性输入4个选项。输入后再遍历结构体数组，进行长度的计算，**记得要-2**.因为最前面的两个字符是不能算进去的（我一开始就写错了QAQ）。   
与此同时我们在结构体数组里也存入选项名

### 3.排序，写出cmp函数

sort排序即可，cmp函数比较长度

### 4.判断以及输出

因为已经进行好了排序，我们只需要判断

>1.最长的选项是第二长选项的2倍及以上，输出最长选项的选项名   
2.第二短的选项是最短选项的2倍及以上，输出最短选项的选项名
3.如1、2两种情况同时出现或均不出现，输出“C”

## 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
string a,b,c,d;
int l,s;
struct node{
	string a;
	int len;
	char h;
}Node[5];
bool cmp(node a,node b){
	return a.len>b.len;
}
int main(){
	cin>>Node[1].a>>Node[2].a>>Node[3].a>>Node[4].a;
	for(int i=1;i<=4;i++){
		Node[i].len=Node[i].a.length()-2;
		Node[i].h=i-1+'A';
	}
	sort(Node+1,Node+5,cmp);
	if(Node[1].len>=2*Node[2].len&&Node[3].len>=2*Node[4].len){
		cout<<"C"<<endl;
		return 0;
	}
	if(Node[1].len>=2*Node[2].len){
		cout<<Node[1].h<<endl;
		return 0;
	}
	if(Node[3].len>=2*Node[4].len){
		cout<<Node[4].h<<endl;
		return 0;
	}
	cout<<"C"<<endl;
	return 0;
}
```


---

## 作者：sysu_yzc (赞：0)

## 思路
先求出四个选项的长度。

然后判断是否有选项的长度不小于其他选项长度的两倍，如有，记为$ans1$。

之后判断是否有选项的长度的两倍不大于其他选项长度，如有，记为$ans2$。

如果$ans1$与$ans2$中只有一个有值，则输出有值的$ans$；

如果$ans1$与$ans2$都没有值，则输出$C$；

如果$ans1$与$ans2$相等，则答案为$ans1$；

如果$ans1$与$ans2$不同，则输出$C$。
## 上代码
```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    string s[4];
    int l[4];
    char ans1=0,ans2=0;
    for(int i=0;i<4;i++){
        cin>>s[i];
        l[i]=s[i].size()-2;
    }//求出四个选项的长度
    for(int i=0;i<4;i++){
        bool f=1;
        for(int j=0;j<4;j++){
            if(i==j) continue;
            if(l[i]<2*l[j]){
                f=0;
                break;
            }
        }
        if(f){
            ans1=i+'A';
            break;
        }
    }
    ans2=ans1;
    for(int i=0;i<4;i++){
        bool f=1;
        for(int j=0;j<4;j++){
            if(i==j) continue;
            if(l[i]*2>l[j]){
                f=0;
                break;
            }
        }
        if(f){
            ans2=i+'A';
            break;
        }
    }
    if((ans1==ans2&&ans1!=0)) cout<<ans1;
    else if(ans1==0&&ans2!=0) cout<<ans2;
    else cout<<"C";
    return 0;
}
```

---

## 作者：CobaltChloride (赞：0)

水过头的特判
```
#include<bits/stdc++.h>
using namespace std;
int len[5][2]={{0,0},{0,1},{0,2},{0,3},{0,4}};//初始化
int big,small;
string a,b,c,d;
int i,j;
int main(){
	cin>>a>>b>>c>>d;
	len[1][0]=a.length()-2;
	len[2][0]=b.length()-2;
	len[3][0]=c.length()-2;
	len[4][0]=d.length()-2;
    //开头两个字符不能算
	for(i=1;i<4;i++){
		for(j=i+1;j<=4;j++){
			if(len[i][0]>len[j][0]){
			    swap(len[i][0],len[j][0]);
			    swap(len[i][1],len[j][1]);//交换
		    }
		}
	}//冒泡排序
	if(len[1][0]*2<=len[2][0]) small=1;//有短的
	if(len[4][0]>=len[3][0]*2) big=1;//有长的
	if(small==big) cout<<'C';//答案不是1个
	else{
		if(small) printf("%c",len[1][1]+64);//输出选项
		if(big) printf("%c",len[4][1]+64);
	}
	return 0;
}
```

---

