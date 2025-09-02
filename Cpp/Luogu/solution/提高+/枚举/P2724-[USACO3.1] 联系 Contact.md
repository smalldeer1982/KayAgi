# [USACO3.1] 联系 Contact

## 题目背景

奶牛们开始对用射电望远镜扫描牧场外的宇宙感兴趣。最近，他们注意到了一种非常奇怪的脉冲调制微波从星系的中央发射出来。他们希望知道电波是否是被某些地外生命发射出来的，还是仅仅是普通的的星星发出的。


## 题目描述

帮助奶牛们用一个能够分析他们在文件中记下的记录的工具来找到真相。他们在寻找长度在 $A$ 到 $B$ 之间（包含 $A$ 和 $B$ 本身）在每天的数据文件中重复次数前 $n$ 多的比特序列。

符合的序列可能会重叠，并且至少出现一次的序列会被计数。

## 说明/提示

#### 输入输出样例 1 解释

在样例里，序列 $100$ 出现了 $12$ 次，而序列 $1000$ 出现了 $5$ 次。次数最多的序列是 $00$，出现了 $23$ 次。

---

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 50$，$1 \leq A \leq B \leq 12$，$s$ 中只含字符 `0` 和字符 `1`，且长度不超过 $2 \times 10^5$。

---
#### 说明

题目翻译来自 NOCOW。

## 样例 #1

### 输入

```
2 4 10
01010010010001000111101100001010011001111000010010011110010000000```

### 输出

```
23
00
15
01 10
12
100
11
11 000 001
10
010
8
0100
7
0010 1001
6
111 0000
5
011 110 1000
4
0001 0011 1100```

# 题解

## 作者：Mingoal (赞：18)

我发一个0ms的代码。

我的思想是枚举长度，把二进制字符串压位，然后累加

详见注释：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4096;
struct kk{
    int x,y,z;
}b[500000];
int A,B,n,m,s[200003],v[N],k,c[13],i,j,t,cnt,to,k1;
char ch;
int cmp(kk x,kk y){
    return x.x>y.x || x.x==y.x && (x.z<y.z || x.z==y.z && x.y<y.y);
}
void chan(int x,int y){//把十进制x转成二进制，y表示二进制位数
    int tot=0;
    while (x){
        c[tot++]=x%2;
        x/=2;
    }
    for (int i=0;i<=y-tot;i++) putchar(48);//位数不够用0补
    for (int i=tot-1;i>=0;i--) putchar(c[i]|48);
}
int main(){
    cin>>A>>B>>n;
    while ((ch=getchar())!=EOF)
        if (ch==48 || ch==49) s[m++]=ch^48;//读入，把'0'和'1'变成0和1，位运算更快
    B=min(B,m);//最长也不能超过总长度
    for (i=0;i<B;i++){
        k=k<<1|s[i];//k记录0..i-1位的序列，k<<1|1相当于k*2+1，但这样更快
        if (i>=A-1){
            t=(1<<i+1)-1;
            memset(v,0,sizeof(v));
            v[k]++;
            k1=k;
            for (j=i+1;j<m;j++){
                k1=(k1<<1|s[j])&t;//这里是取k的二进制后i+1位 %(2^(i+1))相当于&(2^(i+1)-1)，常用技巧，不懂的话下面有解释
                v[k1]++;//记录
            }
            for (j=0;j<=t;j++)
                if (v[j]) b[cnt].x=v[j],b[cnt].y=j,b[cnt++].z=i;//x记录频率，y记录值，z记录长度
        }
    }
    sort(b,b+cnt,cmp);
    j=0;
    for (i=0;i<n && j<cnt;i++){
        printf("%d\n",b[j].x);
        to=1;
        while (b[j+1].x==b[j].x){
            chan(b[j].y,b[j].z);
            j++;
            if (to==6) putchar('\n'),to=0;//没6个换1行
            else putchar(' ');
            to++;
        }
        chan(b[j].y,b[j].z);
        j++;
        if (to) putchar('\n');
    }
}
```
其实代码中还有一些地方可以优化，但是我已经0ms了，也没继续优化

这里说一下为什么当k=2^t时x%k=x&(k-1)

x%k相当于取x二进制末t位

k-1的二进制就是t个1

x末t位0还是0，1还是1，不变

x前面的几位不管是0还是1，因为k的对应位是0，所以也变成0


---

## 作者：「QQ红包」 (赞：9)

题解by：redbag

百度了很多题解，都有写到输出很坑。

然而我想说的是

###**输出太坑了。**

usaco对格式要求太严格了。


0. 输出完频率要换行。

0. 输出6个序列要换行。

0. 输出完序列要换行。

0. 如果该频率的序列刚好是6个的话只要换一次行。

0. 每行第一个序列之前不能有空格。

0. 每行最后一个序列之后不能有空格。


关于排序


0. 频率高的在前。

0. 频率一样时，位数少的在前。

0. 位数也一样时，字典序小的在前。


存的话用map来存每个序列对应的编号。

x[i/\*i为标号\*/].s存这个序列，x[i].a存频率。

然后才能不愉快的AC。

```cpp

/*
ID: ylx14271
PROG: contact
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm>
#define LL unsigned long long
using namespace std;
map<string,int> s;
int a,b,n,i,j,k,len,ls,xx;
char ch;
char c[5000000];
struct haha
{
    string s;
    int a;
}x[100100];
int cmp(haha aa,haha bb)
{
    if (aa.a>bb.a) return 1;//频率从小到大排序 
    if (aa.a==bb.a)//频率相等 
    {
        if (aa.s.size()<bb.s.size())return 1;//长度短的在前 
        if (aa.s.size()==bb.s.size()&&aa.s<bb.s)return 1;//字典序小的在前 
        return 0; 
    } 
    return 0;
} 
int main()
{
    freopen("contact.in","r",stdin);
    freopen("contact.out","w",stdout);
    scanf("%d %d %d\n",&a,&b,&n);
    while ((ch=getchar())!=EOF)//读入 
    {
        if (ch=='1'||ch=='0') 
        {
            len++;//len：统计位数的 
            c[len]=ch;//存起来
            //len作为某个串的结尾，枚举开头
            string ss="";
            int B=max(len+1-b,1);//一定要比1大  
            for (i=len;i>=B;i--)
            {
                ss=c[i]+ss;//要加在前面，我就不用substr 
                if (len-i+1>=a)//长度>=a 
                    {
                        if (s[ss]==0)//从未出现
                        {
                            ls++; 
                            s[ss]=ls;//标记 
                            x[s[ss]].s=ss;//储存 
                        }
                        x[s[ss]].a++;//统计 
                    } 
            }
        }
    }//尼玛要怎么输出啊 (╯▽╰),好坑
    sort(x+1,x+ls+1,cmp);//从大到小排序
    for (i=1;i<=ls;i++)
    {//N个频率最高的序列要全部输出完才能退出 
        if (n==0&&x[i].a!=x[i-1].a) break;
        if (x[i].a==x[i-1].a)//和上一个出现次数一样
        {
            if (xx%6==0) cout<<x[i].s;//每一行的开头不要加空格 
            else cout<<" "<<x[i].s;//否则就要加空格 
            xx++;
            if (xx%6==0) printf("\n");//6个一换行 
        }
        else
        {
            n--;//又输出了一个出现频率 
            if (i!=1&&xx%6!=0) printf("\n");
//出现之前那个频率的串，如果是6的倍数，结尾就换行了，在此就不用再换行了。 
            printf("%d\n",x[i].a);//输出完频率之后换行 
            cout<<x[i].s;//再输出串 
            xx=1;//重新统计 
        }
    } 
    if (xx%6!=0) printf("\n");//如果最后一个数有6个的话， 
    return 0;
}```

---

## 作者：LikC1606 (赞：4)

# 特坑题
## 题意
给你一个字符串（会有换行），求出在长度A~B的01字符串出现最多的N种（出现次数一样多的算一种），输出它的次数以及分别是哪些字符串，出现次数为第一关键字，字符串的长度为第二关键字，字符串的大小（也就是二进制化为整数的大小）为第三关键字。
## 做法
第一眼看时觉得挺水，感觉只有普及+左右的难度，就是普通的暴力枚举，但是用DFS会超时，所以要用一些技巧，也就是位运算的技巧，把二进制强压成十进制数，就不用一位一位的比较了，再用结构体sort排序，在输出就行。
## 坑点
1.枚举的时间复杂度是关键，如果你不信，可以用暴力枚举尝试（第五个点和第七个点会让你怀疑人生）；

2.输入时的换行；

3.输出是的每六个一行以及末尾不能有空格（六个一行时要注意：当接下来没有答案时，不能换行（本人卡这多时））；
##  代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int A,B,N;
char s[200010];
int ans=0;//记录出现过的二进制数的个数（因为要排除未出现的） 
int n;
struct t 
{
    int len, value, cnt;
}pinlu[20010];//len是二进制数的长度，value是二进制化十进制的结果，cnt是出现次数 

bool cmp(t x,t y)
{
	if(x.cnt==y.cnt) 
	{
		if(x.len==y.len) return x.value < y.value;
		return x.len < y.len;
	}
	return x.cnt > y.cnt;
}

void print(int l, int v)
{
	for (int i = l-1; i >= 0; --i)
		putchar('0'+ ((v>>i)&1));//将十进制化为二进制后输出 
}
int main() 
{
    cin>>A>>B>>N;
    while (true)
    {
    	char ch = getchar();
    	if (ch == EOF) break;
    	if (ch == '0' || ch == '1')
    		s[++n] = ch;
	}
	int ans=0;
	for(int m=A;m<=B;++m)
	{
		int cnt[1<<12]={};
		int sum=0;
		for(int i=1;i<=m;++i)
		   sum*=2,sum+=s[i]-'0';//二进制十进制 
		for(int i=m;i<=n;++i)
		{
			cnt[sum]++;
			if(s[i-m+1] == '1') sum-=(1<<(m-1));
			sum*=2;
			sum+=s[i+1]-'0';//技巧计算 
		} 
		for(int i=0;i<(1<<m);++i)
		  if(cnt[i]) pinlu[++ans].len=m,pinlu[ans].cnt=cnt[i],pinlu[ans].value=i;
	}
	sort(pinlu+1,pinlu+ans+1,cmp);//排序 
	int ss=0;//ss记录种类数 
	int now=0;//now记录当前轮到的二进制数 
	while(ss<N&&now<ans)
	{
		++ss;
		++now;
	    if(ss!=1) cout<<endl;//在第一次的输出后换行 
		cout<<pinlu[now].cnt<<endl;//输出种类数 
		print(pinlu[now].len,pinlu[now].value);
		int lh=1;//后面的换行记录 
		for(int i=now+1;i<=ans;++i)
		{
		   if(pinlu[i].cnt==pinlu[now].cnt)//判断出现次数是否相等 
		    {
		    	if(lh%6!=0) cout<<" "; 
		    	print(pinlu[i].len, pinlu[i].value);
				++now;
				++lh; 
				if(lh%6==0&&pinlu[i+1].cnt==pinlu[now].cnt) cout<<endl;//每六个换行，判断是否有“第七者” 
		    }
            else break;//如果没有找到就跳出 
	    }
    }	
    cout<<endl;
	return 0;
}
```


---

## 作者：stoorz (赞：4)

[$$\color{blue}\texttt{链接:蒟蒻的Blog}$$](https://blog.csdn.net/SSL_ZYC/article/details/89055398)

![](https://i.loli.net/2019/04/06/5ca83f453ecb8.png)
由于$A,B\leq12$，所以显然把01串状压。

状压之后用$cnt[S]$表示压缩后为$S$的状态个数。

但是这样忽略了前导零的情况。

也就是说，如果我们能找到这样的两个子串

```
00101
101
```


我们都会压缩成5。但是这两个串是不同的。

所以我们在$cnt$数组上再加上一维，设$cnt[S][i]$表示状态为$S$，有$i$个前导零的子串个数。（其实也可以设01串位数为$i$位，但是敲完了就懒得改了XD）

那么考虑如何枚举出长度在$l\sim r$的所有子串。

如果我们知道了第$i\sim j$位压缩后的状态，第$j+1$位是$x$，需要我们推出$i\sim j+1$位压缩后的状态，显然`就是把i∼j位的状态左移一位，然后加上x`。

所以当我们枚举到原串第$i$位开始的子串时，设$num[j]$表示长度为$j$的子串压缩后的状态（即$i\sim j$维压缩后的状态）。那么显然可以这样推出


```cpp
for (int j=min(i,r);j>=1;j--)
	num[j]=(num[j-1]<<1)+x;
```

然后更新$cnt$


```cpp
for (int i=l;i<=min(j,r);i++)
	cnt[num[i]][count(i,num[i])]++;
```
其中$count$用来计算有多少位前导零。

接下来就需要给$cnt$数组按值排序了。

显然是不可能用$sort$的。因为一个值可能会对应多个状态。
所以可以考虑用队列。

设$q[i]$表示出现次数为$i$的子串集合。$q[i].first$表示该子串状压后的状态，$q[i].second$表示该子串的长度。

然后按照题目要求，先枚举子串长度，然后按字典序枚举子串的状态。并加入队列。

```cpp
for (int j=l;j<=r;j++)
	for (int i=0;i<(1<<j);i++)
		q[cnt[i][count(j,i)]].push(make_pair(i,j));
```
然后就是输出的事情了。

根据[$redbag$大爷的题解](https://www.luogu.org/blog/ylx/solution-p2724)，有以下几点输出要求：

 1.  输出完频率要换行。
 2. 输出6个序列要换行。
 3. 输出完序列要换行。
 4. 如果该频率的序列刚好是6个的话只要换一次行。
 5. 每行第一个序列之前不能有空格。
 6. 每行最后一个序列之后不能有空格。

细节处理一下就好了。从大到小枚举子串出现次数$i$，如果存在出现$i$次的子串，一一输出就好了。我们在加入队列的时候已经保证了子串长度和字典序，所以可以不用在意输出顺序。

时间复杂度大约是$O(|S|\times r+max\{cnt\})$。

```cpp
/*
ID:ssl_zyc2
TASK:contact
LANG:C++
*/
#include <cstdio>
#include <queue>
#include <iostream>
#define mp make_pair
using namespace std;

const int N=200010;
int l,r,n,x,maxn,num[15],cnt[1<<12][15];

int count(int s,int x)
{
	if (!x) return s-1;
	int sum=0;
	while (x)
	{
		x>>=1;
		sum++;
	}
	return s-sum; 
}

void print(int x)
{
	if (x>1) print(x>>1);
	printf("%d",x&1);
}

int main()
{
	freopen("contact.in","r",stdin);
	freopen("contact.out","w",stdout);
	scanf("%d%d%d",&l,&r,&n);
	for (int j=1;scanf("%1d",&x)==1;j++)
	{
		for (int i=min(j,r);i>=1;i--)
			num[i]=(num[i-1]<<1)+x;
		for (int i=l;i<=min(j,r);i++)
		{
			cnt[num[i]][count(i,num[i])]++;
			maxn=max(maxn,cnt[num[i]][count(i,num[i])]);
		}
	}
	queue<pair<int,int> > q[maxn+1];
	for (int j=l;j<=r;j++)
		for (int i=0;i<(1<<j);i++)
			q[cnt[i][count(j,i)]].push(mp(i,j));
	for (int i=maxn;i>=1&&n;i--)
		if (q[i].size())
		{
			n--;
			printf("%d\n",i);
			int len=q[i].size();
			for (int j=1;j<=len;j++)
			{
				for (int k=1;k<=count(q[i].front().second,q[i].front().first);k++)
					putchar(48);  //输出前导零
				print(q[i].front().first);
				q[i].pop();
				if (!(j%6)) printf("\n");
					else if (j!=len) printf(" ");
			}
			if (len%6) printf("\n");
		}
	return 0;
}
```


---

## 作者：L_M_ (赞：3)

这题巨多坑点啊，就算算法对了也D了半个小时orz

看到题目，我的想法是记录每种串的出现次数，将串转成二进制计算值即可。由于010和0010可能被重复计在一起，所以要限制长度k

所以,用cnt[k][i]表示长度为k，值为i的串的出现次数

但稍等！如果我们每个串都计算一次，那么是会超时的，这里就要用到一个技巧：滚动哈希

考虑一个串110110101,长度为3，现在我们算出了110的哈希值为5，那么怎么算下一位101的值呢？

稍加分析即可发现，我们将110向左移一位变成1100,现在我们得去掉最高位的1，就将它& ((1<<k) - 1）（即为0111，这样就除去了超过三位的数字），再将它或目前的值，就能O(1)得到当前哈希值

这样，复杂度就为O(nb),可以通过本题

但这道题的坑点不在此，而是输出和特判！！

输出的换行和细节具体见代码，还有就是如果a > b直接return 0 ,如果b > len，那么将b变为len即可，见代码

以上
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<climits>
#include<queue>
using namespace std;
const int maxn = 2e5 + 5;
inline int read()
{
    int ans = 0,op = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') op = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        (ans *= 10) += ch - '0';
        ch = getchar();
    }
    return ans * op;
}
int aa,b,n;
int cnt[13][1 << 12];
char s[maxn];
char ss[110];
int a[maxn];
int invert(int s,int e)
{
    int ans = 0;
    for(int i = s;i <= e;i++)
    {
        (ans += a[i]) *= 2;
        //cout << a[i];
    }
    return ans >> 1;
}
int ans[20];
void rebuild(int k,int len)
{
  int temp = len;
  memset(ans,0,sizeof(ans));
    while(len--)
    {
      ans[len] = k & 1;
      k = k >> 1; 
    }
 for(int i = 0;i < temp;i++) printf("%d",ans[i]);
}
struct node
{
    int v,len,tv;
    bool operator < (const node& a) const
    {
      if(v != a.v) return v > a.v;
      else if(len != a.len) return len < a.len;
      else return tv < a.tv;
    }
}st[maxn];
int top;
int len;
int main()
{
    aa = read(),b = read(),n = read();	
    while(scanf("%s",ss + 1) != EOF)
    {
    	for(int i = 1;i <= strlen(ss + 1);i++)
    	{
    		len++;
    		s[len] = ss[i];
    	}
    }
    b = min(b,len);
    if(aa > b) return 0;
    for(int i = 1;i <= len;i++) a[i] = s[i] - '0';
    for(int k = aa;k <= b;k++)
    {
        int temp = invert(1,1 + k - 1);
        cnt[k][temp]++;
        for(int i = k + 1;i <= len;i++)
        {
            temp = ((temp << 1) & ((1 << k) - 1)) | a[i];
            cnt[k][temp]++;
        }
    }
    for(int k = aa;k <= b;k++)
        for(int i = 0;i <= (1 << k) - 1;i++)
          if(cnt[k][i]) st[++top].v = cnt[k][i],st[top].len = k,st[top].tv = i;
    sort(st + 1,st + 1 + top);
    int j = 1;
    for(int i = 1;i <= n;i++)
        {
            if(j > top) break;
            printf("%d\n",st[j].v);
            int tot = 1;
            rebuild(st[j].tv,st[j].len);
            printf(" ");
            while(st[j].v == st[j + 1].v && j + 1 <= top)
            {
                j++;
                rebuild(st[j].tv,st[j].len);
                tot++;
                printf(" ");
                if(tot >= 6) { printf("\n"); tot = 0; }
            }
            j++;
            if(tot) printf("\n");
        }
    //cout << endl;
}

```


---

## 作者：珅肐 (赞：1)

#### 提供新的处理前导零的方法

一看题目，显然就是$(B-A+1)*len$的做法

因为$A$、$B$很小，考虑状压。

状压之后就可以用数组储存，如果用对应的二进制表示，十二位最多有$2^{12}$种，可以轻松的用数组存下。

但实际过程中我们会遇到问题，如我们无法区分$1$、$01$、$001$等这样带有前导零的数字， 

大部分题解选择了同时记录长度，

也有人把$01$颠倒，或者利用康托展开把二进制转为十进制，把$0$变成$2$，但这样就大大增加了排序的难度

还有的用了$map$？

其实我们只要在前面加上一个$1$，像是上面的三个变成$11$、$101$、$1001$

就不再出现前导零的问题

而且这样的话，排序也方便了许多，长度短的本来字典序就小

而二进制的字典序就是从小到大来的，所以我们直接对存的数排序，就解决了所有问题

这样的话空间多了一倍，但还是很小（$2^{13}=16384$）

### 详见代码：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){//超级快但这道题没有用的快读
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
struct OOO{//结构体存序列
	int id,cnt;//id表示二进制转化成int的数，cnt表示频率
	bool operator <(OOO b)const{//排序函数，先按频率排，然后按字典序（即数的大小）
		if(cnt==b.cnt)return id<b.id;
		return cnt>b.cnt;
	}
}f[16387];
char s[87];//辅助读入数组
int a[200007];//存整个序列
inline void put(int x){//输出
	for(int i=13;i>=0;--i)
		if((x&(1<<i))){找到第一位1，因为这一位是我们自己加的，所以从下一位开始
			for(int j=i-1;j>=0;--j)putchar((x&(1<<j)?1:0)+48);//挨个输出每个二进制位
			break;//退出循环
		}
}
int main(){
	int A=read(),B=read(),n=read(),m=B-A+1;
	int l=0,o=0;
	while(scanf("%s",s)!=EOF)for(int i=0;i<strlen(s);++i)a[++l]=s[i]^48;//转化成int，方便处理
	//下面是状压过程
    for(int i=1;i<A;++i)o=o<<1|a[i];//o滚动记录A-1位序列
	for(int i=A;i<=l;++i){
		int p=o|(1<<A-1);//这是增加一位1
		for(int j=0;j<m && i+j<=l;++j){
			p=p<<1|a[i+j];//每次乘2，增加一位
			f[p].cnt++,f[p].id=p;//存储频率和数的大小
		}
		o=o%(1<<A-1)<<1|a[i];//o%(1<<A-1)是去掉最前面上一位，<<1|a[i]是再增加一位
	}
	sort(f,f+16387);//排序
	int i=0,cn=0;//稍稍恶心的输出。
	while(f[i].cnt && ++cn<=n){//要保证频率不为零且只输出n个
    		printf("%d\n",f[i].cnt);
		int j=i-1;
		do{//do-while循环方便一些
			put(f[++j].id);
			if((j-i+1)%6==0)puts("");(j-i+1)是到目前为止的长度，若是6的倍数，就换行
			else putchar(' ');
		}while(f[j+1].cnt==f[j].cnt);
		if((j-i+1)%6)puts("");//如果不是6的倍数，就不换行
		i=j+1;//i跳到j的下一个位置，留到下次循环继续做
	}
	return 0;//好习惯
}


```


---

## 作者：MornEveGlow (赞：0)

这题由于我的暴力算法坑了我好久……

1. 想到人人都有想到的状压：把一个字符串压成一个int。

2. 然后枚举字符串算CNT。但是前导零会有歧义怎么办呢？同时存上长度。

3. 这时，我们可以使用一个**vector<pair<int,int> > V[i]指出现次数为i的字符串**。其中pair的**first是压出的int，second是字符串长度**。

第三步核心代码如下：
```cpp
vector<pair<int,int> > P[N];
...
void D2B(int x,int l){
    for(int i=l-1;~i;--i)
        printf("%d",(x&(1<<i))>0);
}
...
int main(){
	...
	for(int i=a;i<=b;++i)
	for(int j=0;j<1<<i;j++)
		P[Cnt[j][i]].push_back(make_pair(j,i));
	for(int i=l;i&&n;--i)
		if(P[i].size()){
			printf("%d\n",i);
			for(int j=0;j*6<P[i].size();++j){
				D2B(P[i][j*6].first,P[i][j*6].second);
				for(int k=1;k<6&&j*6+k<P[i].size();++k){
					printf(" ");
					D2B(P[i][j*6+k].first,P[i][j*6+k].second);
				}
				printf("\n");
			}
			--n;
		}
}
```

PS：事实上我是因为用了个更慢的第二步而卡的。

---

## 作者：lenaalyth (赞：0)

各位大佬的代码好厉害。。。这里提供一个蒟蒻的思路，由题意可知，这里的字串只有1和0构成，于是乎可以直接用二进制来代替。。。出现了问题，零前置怎么办：将一和零的作用颠倒，用二维数组存起来。。。但这道题麻烦的不是方法。。。而是输入输出排序。。。
1.输入：直接到文件结尾（被卡了好多次。。。）
2.输出：控制输出个数，每行六个，注意最后一行没有到六个也要换行
3.排序：先按出现数目，后按字符串长度，在后按大小。。。。
以下是代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;
int i,d,n,m,g,h,j,ps;
string l,q,mp[100000];
typedef struct{
    int ss;
    string x;
}fhs;
fhs a[2][5000],bm[100000];
int zh1(string b)
{
int m=0;
for(int x=b.size()-1;x>=0;x--)
{
    if(b[x]=='1')
    m+=(int)pow(2.0,(double)(b.size()-1-x));
}
return m;
}
int zh2(string bl)
{
int m=0;
for(int x=bl.size()-1;x>=0;x--)
{
    if(bl[x]=='0')
    m+=(int)pow(2.0,(double)(bl.size()-x-1));
}
return m;
}
string hz1(int x)
{
    string m;
    int nlog=log((double)x)/log(2.0);
    for(int v=nlog;v>=0;v--)
    {
        if(x>=(int)(pow(2.0,double(v))))
        {
            m+='1';
            x-=(int)(pow(2.0,double(v)));
        }
        else
        {
            m+='0';
        }
    }
    //reverse(m.begin(),m.end());
    return m;
}
string hz2(int x)
{
string m;
    int nlog=log((double)x)/log(2.0);
    for(int v=nlog;v>=0;v--)
    {
        if(x>=(int)(pow(2.0,double(v))))
        {
            m+='0';
            x-=(int)(pow(2.0,double(v)));
        }
        else
        {
            m+='1';
        }
    }
    //reverse(m.begin(),m.end());
    return m;
}
bool cmp(fhs a1,fhs a2)
{
    if(a1.ss!=a2.ss)
    {
        return a1.ss>a2.ss;
    }
    else
    {
        if(a1.x.size()==a2.x.size())
        return zh1(a1.x)<zh1(a2.x);
        else
        return a1.x.size()<a2.x.size();
    }
}

int main()
{
    for(int x=1;x<5000;x++)
    {
        a[1][x].ss=0;
        a[1][x].x=hz1(x);
    }
    for(int x=1;x<5000;x++)
    {
        a[0][x].ss=0;
        a[0][x].x=hz2(x);
    }
    a[0][1].ss=0;
    a[0][1].x="0";
    cin>>i>>d>>n;
    while(cin>>q)
    {
    	l+=q;
	}
	//cin>>l;
    int pa=0;
    int mmp=l.length();
    j=min(d,mmp);
    for(int x=i;x<=j;x++)
    for(int y=0;y<=mmp-x;y++)
    {string ll;
    for(int z=0;z<x;z++)
    {
        ll+=l[y+z];
    }
    if(ll[0]=='0')
    {
        int u=zh2(ll);
        a[0][u].ss++;
    }
    else
    {int u=zh1(ll);
        a[1][u].ss++;
    }
   /* if(x==12)
    {

        cout<<ll<<endl;
    }*/
    }
    for(int x=0;x<2;x++)
    for(int y=0;y<5000;y++)
    {
        if(a[x][y].ss!=0)
        {
            bm[pa].ss=a[x][y].ss;
            bm[pa++].x=a[x][y].x;
        }
    }
    bm[pa].ss=0;
    bm[pa].x="a";
    sort(bm,bm+pa,cmp);
    int du=0,cs=1331313,mnmn=0;
    for(int x=0;x<=pa||cs-1==0;x++)
    {
        if(x==0)
        {
            cs=bm[x].ss;
        }
        else
        {

            if(cs!=bm[x].ss&&cs!=0)
            {
                cout<<cs<<endl;
                int v=du;
                for(;du<x;du++)
                {
                    cout<<bm[du].x<<" ";
                    if((du-v)!=0&&(du-v)%6==5)
                    {
                        cout<<endl;
                    }
                }
                if((du-v)%6!=0)
                cout<<endl;
                cs=bm[x].ss;
                mnmn++;
            }
        }
        if(mnmn==n)
            return 0;
    }

}

```
如果出现疏忽的地方还望大佬们指点。。。。

---

## 作者：Celebrate (赞：0)

这一道题利用康托展开把二进制转化为十进制，并且录，输入

中间有一个细节，就是比如说010101，应该一开始就变成121212，这样就不会因为长度的不同而出现错误了

完字符串以后逐个搜索，找完后排序一遍然后输出

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,a[610000];//a记录出现过的数
int A,B,n,len;
char st[210000],ss[110];
int f[610000];//把二进制变成十进制后的数
int kt[21],t;//kt记录每一位的字符
inline int kangtuo()//康托展开
{
    int ans=0,s=1;
    for(int i=t;i>=1;i--)//记得反过来求
    {
        ans=ans+kt[i]*s;
        s*=3;
    }
    return ans;
}
inline int kangtuo_(int x)//输出把x变成十进制并且输出
{
    int lenth=0,g[51];
    while(x>0)
    {
        lenth++;g[lenth]=x%3;
        x/=3;
    }
    for(int i=lenth;i>=1;i--) printf("%d",g[i]-1);//反着输出，并且-1
}
inline int cmp(const void *xx,const void *yy)//排序
{
    int x=*(int*)xx;
    int y=*(int*)yy;
    if(f[x]>f[y]) return -1;//按频率排序
    if(f[x]<f[y]) return 1;
    if(x>y) return 1;//按照大小排序
    if(x<y) return -1;
    return 0;
}
int main()
{
    int i,j;
    scanf("%d%d%d",&A,&B,&n);
    while(scanf("%s",ss+1)!=EOF)//每次输入
    {
        for(int i=1;i<=strlen(ss+1);i++)//记录
        {
            len++;st[len]=ss[i];
        }
    }
    for(i=1;i<=len;i++) st[i]++;//把全部的字符都搜索一遍
    B=min(B,len);//B的长度再怎么长也不能比len长
    if(A>B) return 0;//如果要找的长度比给出的长度还长，就不用管了
    for(i=1;i<=len;i++)
    {
        t=0;
        if(len<i+A-1) break;
        for(j=i;j<=min(len,i+B-1);j++)
        {
            t++;kt[t]=st[j]-'0';//记录字符
            if(t>=A)//如果满足要求了
            {
                int tt=kangtuo();//把这个数变成十进制
                f[tt]++;
                if(f[tt]==1) //如果只出现了一次
                {
                    m++;
                    a[m]=tt;//记录这个字符
                }
            }
        }
    }
    qsort(a+1,m,sizeof(int),cmp);//排序
    i=1;int s=1;
    for(i=1;i<=n;i++)//输出，如果没有那么多的话就输出能找到的所有
    {
        printf("%d\n",f[a[s]]);//输出
	t=0;
        for(j=s;j<=m;j++)
        {
            if(f[a[j]]==f[a[s]])//如果它们的频率相同
            {
                kangtuo_(a[j]);//输出二进制下的数
		if(j==m) //如果全部找完了
		{
			printf("\n");return 0;//就直接输出
		}
                printf(" ");
                t++;if(t%6==0) printf("\n");//如果够留个了，就换行
            }
            else 
            {
                s=j;break;//不相同的话就记录这个数
            }
        }
        if(t%6!=0) printf("\n");//如果前面没有换过行，就换行
    }
    return 0;
}
```

---

## 作者：立花泷 (赞：0)

这题数据看起来很大，其实是可以接受的。扫描整个01串，找出所有长度在A到B之间的子串，用cnt数组计数再用优先队列输出前n即可，需要尤其注意格式。

这题我的方法是把所有长度在A到B之间的01串编码成0~65535之间的整数，输出时还原即可。编码时要存储串本身和串的长度两个信息（否则0, 00, 000这些串将无从区分）。

代码(43ms,目前最优)：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define MAXN 200005
using namespace std;
typedef unsigned short str; //使用unsigned short来存储01子串
struct Kinds{ //Kinds表示一种子串(a KIND of Str)，在优先队列中使用
    int n; //该串出现的次数
    str s; //该串本身
    //以下是构造和析构函数
    Kinds(int tn,str ts){
        n=tn,s=ts;
    }
    Kinds(void){
        n=0;s=0;
    }
    ~Kinds(void){}
    //友元小于运算符，优先队列用
    friend bool operator<(const Kinds lhs,const Kinds rhs);
};
char sstr[MAXN]; //用来存储输入的字符序列
int cnt[65536]={0}; //cnt数组，用于给每一种串计数
str shash(char *,int); //char串->整数编码
int unshash(str,char *); //整数编码->char串
int main(void){
    int a,b,n,len; //len存储整个字符序列的长度
    char linet[25];//输出时使用的缓存
    char chart;  //输入缓存
    int i,l,last,tmpn; //分别为循环变量(数组索引位置)、循环变量(枚举长度)、输出用变量、输出用变量（专门满足题目苛刻的格式要求）
    priority_queue<Kinds> q; //输出用的优先队列
    Kinds tmp;
    cin >> a >> b >> n;
    i=0;
    while ((chart=getchar())!=EOF)
        if (chart=='0' || chart=='1')
            sstr[i++]=chart;
    
    len=i;
    //以上为输入字符序列
    
    for (l=a;l<=b;l++)
        for (i=0;i<=len-l;i++)
            cnt[shash(sstr+i,l)]++;
    
    //以上为枚举和统计每种串
    for (i=0;i<65536;i++)
        if (cnt[i]>0)
            q.push(Kinds(cnt[i],str(i)));
    //以上为将出现的串放进优先队列里

    last=-1,tmpn=0,i=0;
    while (!q.empty()){
        tmp=q.top();
        q.pop();
        if (tmp.n!=last){
            last=tmp.n;
            tmpn=0;
            i++;
            if (i>n)
                break;
            if (i>1)
                cout << endl;
            cout << last << endl;
        }
        if (tmpn==6){
            cout << endl;
            tmpn=0;
        }
        unshash(tmp.s,linet);
        cout << linet << ' ';
        tmpn++;
    }
    //以上为输出
    cout << endl; //控制台调试时为了美观加上的，评测时可删除
    return 0;
}
str shash(char * a,int l){
    //char串->整数编码，两个参数为char串和串的长度，返回编码串
    //编码的结构：从高位到低位，前12位为子串本身，后4位存储串的长度信息
    str s=0;
    int i;
    for (i=0;i<l;i++)
        s=(s<<1)|(a[i]-'0');//相当于s=s*2+(a[i]-'0')
    s=(s<<4)+l;//相当于s=s*16+l
    return s;
}
int unshash(str s,char * a){
    //整数编码->char串，两个参数为编码串和存储char串的位置，返回串的长度
    int l,i;
    l=s&15;//相当于l=s%16
    s=s>>4;//相当于s/=16
    for (i=l-1;i>=0;i--){
        a[i]=(s&1)+'0'; //相当于a[i]=(s%2)+'0'
        s=s>>1; //相当于s/=2
    }
    a[l]='\0'; //为了输出正常，特加上这一行
    return l;
}

bool operator<(const Kinds lhs,const Kinds rhs){
    //比较函数
    if (rhs.n!=lhs.n)
        return lhs.n<rhs.n; //出现次数多的排在前面
    if (((rhs.s)&15)!=((lhs.s)&15))
        return ((lhs.s)&15)>((rhs.s)&15); //长度短的排在前面
    return (((lhs.s)>>4))>(((rhs.s)>>4)); //二进制表示小的排在前面
}
```

---

## 作者：Jason_Yvan (赞：0)

这道题考格式考的不是一般可以， 首先输入的**字符串会有多行**（注意别入坑）， 然后输出**不能有多余空行和空格**（并且输出6个字符串就要换一次行，然后第一个字符串前和最后一个字符串后不能有空格）。

注意排序！！！

**1.出现次数最多的在前面；**

**2.字符串最长的在前面；**

**3.字符串按字典树排序；**


我用了一个 map <string, int> id 表示当前字符串出现的编号

然后我暴力提取 每一节字符串来算出现的次数（事实证明没有TLE）

其他的就按题目的意思来弄就行了。

代码内解释很详细了

C++代码如下：

/*************************************************************************

    > Author: wzw-cnyali
    > Created Time: 2017/3/27 20:15:46
************************************************************************/















```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define EREP(i, a) for(register int i = (be[a]); i != -1; i = nxt[i])
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int Size = 200020;
const int inf = 0x3f3f3f3f;
map <string, int> id;
string S;
struct node
{
    string s;//当前字符串
    int time;//出现次数
    friend bool operator < (node a, node b)//比较函数
    {
        if(a.time == b.time)
        {
            if(a.s.length() == b.s.length())
                return a.s < b.s;
            else 
                return a.s.length() < b.s.length();
        }
        return a.time > b.time;
    }
}contact[Size];
int cnt;
int ID(string s)//给字符串编号
{
    if(!id.count(s)) id[s] = ++cnt;//判断当前字符串是否出现过
    return id[s];
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    int A = read(), B = read(), N = read();
    string s;
    while(cin>>s) S += s;//输入
    REP(i, 0, S.length() - 1)
    {
        for(int j = A, _end_ = S.length(); j <= B && i + j <= _end_; ++j)
        {
            s = S.substr(i, j);//提取字符串 S 中   从第 i 位开始长度为 j 的字符串
            int ls = ID(s);
            contact[ls].s = s;
            contact[ls].time++;
        }
    }
    sort(contact + 1, contact + cnt + 1);//排个序
    int ans = 0;
    REP(i, 1, cnt)
    {
        printf("%d\n", contact[i].time);
        int ls = 0;
        while(contact[i].time == contact[i + 1].time)//判断是否后面有没有出现相同次数的
        {
            cout<<contact[i].s;
            ls++;
            if(ls % 6 == 0) puts("");
            else printf(" ");
            i++;
        }
        cout<<contact[i].s<<endl;//最后一个要换行
        if(++ans == N) break;
    }
    return 0;
}
```

---

