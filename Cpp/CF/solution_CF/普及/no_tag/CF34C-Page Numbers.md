# Page Numbers

## 题目描述

《Bersoft》公司正在致力于开发一款新的编译器，当然，开发一款编译器有很多步骤，公司命令你完成接下来的任务。

用户会输入一串数字，用逗号分割，你的任务就是把这些数字统计出来（不考虑重复的数字），如果出现类似这样$a,a+1,a+2,a+3,\cdots ,a+n$ 的一串数字，你需要把它表示成a - a+n这种形式，单独的数字就不必处理了。

## 样例 #1

### 输入

```
1,2,3,1,1,2,6,6,2
```

### 输出

```
1-3,6
```

## 样例 #2

### 输入

```
3,2,1
```

### 输出

```
1-3
```

## 样例 #3

### 输入

```
30,20,10
```

### 输出

```
10,20,30
```

# 题解

## 作者：chlchl (赞：10)

## 题目意思
题目意思就是输入若干页码（$\leq 1000$），让你化简这些页码。

化简规则：
1. 要去重。
2. 如果出现连续页码（比如说 $1$，$2$，$3$），输出格式为起点 $-$ 终点（$1-3$）。

## 算法及思路
本题为暴力模拟题。

我们先开一个桶（~~看到这个数据范围我就手痒~~），将出现过的页码标记为 $1$，就天然完成了去重。

接着，我们从 $1$ 到 $1000$ 进行循环枚举，如果枚举到某一个页码出现过，那么再开一重循环判断它后面有多少个连续的数出现过，一旦没有出现过就结束循环。最后统计输出即可。

## 一些小坑
这题比较良心，坑点不多。
- 输入时并没有说输入多少个，记得处理一下。
- 输出时记得处理逗号问题。
- 防止重复输出（例如先输出了 $1-3$，又输出了 $2-3$）。

## 代码
以下代码仅供参考。珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1000 + 10;
int x, t[N];
char c;
bool flag;

int main(){
	while(cin >> x){//直接这样输入即可，可以Ctrl+Z结束输入
		cin >> c;//逗号过滤一下
		t[x] = 1;//标记为出现过
	}
	for(int i=0;i<=1000;i++){
		if(t[i] == 1){
			int j, cnt = 1;
			for(j=i+1;j<=1000;j++){//看看后面有多少个连续的数出现过
				if(t[j] == 0)	break;
				cnt++;
			}
			if(cnt > 1){//如果是连续多个数出现，就要写成起点-终点的形式
				if(!flag){
				    //flag用来判断是否第一个输出，如果是，不用在前面输出逗号
					flag = 1;
					cout << i << '-' << j - 1;
				}else	cout << ',' << i << '-' << j - 1;
			}else{//如果仅仅是单个数出现，直接输出这个数即可
				if(!flag){
					flag = 1;
					cout << i;
				}else	cout << ',' << i;
			}
			i = j - 1;//防止重复输出，同时也节省时间
		}
	}
	cout << endl;
	return 0;
}
```
本篇题解到此结束，如果对你有帮助别忘了点个赞哦！

---

## 作者：dsaykc233 (赞：3)

~~本题有点小麻烦~~

思路如下

1. 输入时，要将每个数存储在数组里
1. 排序去重
1. 查找连续数

详细见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define	fo(a,b,c) for(int a=b;a<=c;++a)
#define fr(a,b,c) for(int a=b;a>=c;--a)
#define ll long long
#define pq priority_queue
inline int read()//快出天际的快读 
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main()
{
	char ins[1001];
	int a[101],t=0;
	cin>>ins;
	for(int i=0;i<strlen(ins);++i)
	{
		if(ins[i]==',')
			continue;
		int ans=0;
		while(ins[i]!=','&&i!=strlen(ins))//存储数字 
		{
			ans=ans*10+(ins[i]-'0');
			++i;
		}
		--i;
		a[++t]=ans;
	}
	sort(a+1,a+t+1);//排序 
	t=unique(a+1,a+t+1)-(a+1);//去重
	//神一般的algorithm函数 
	fo(i,1,t)
	{
		int k=i;
		while(a[i+1]-a[i]==1)//是否连续 
			++i;
		if(i!=k)
			printf("%d-%d",a[k],a[i]);
		else
			printf("%d",a[k]);
		if(i!=t)
			printf(",");//判断逗号		
	}
    return 0;
}

```


---

## 作者：Siyuan (赞：1)

## 本题思路：
1. 首先是读入的问题。此处采用`getchar`的形式。$x$记录当前的数字。如果读到 `,` 则在数组中插入$\ x$，否则更新$\ x$（需要注意很多细节）。
2. 由于题意所述：“不考虑重复数字，$\ r_i+1<l_{i+1}$”。于是需要对数组进行排序并去重。
3. 扫一遍数组，对于每个数查找它以后的连续等差数列（连续加减$\ 1$）。如果没有则输出该数字，否则输出等差数列首位项。

### 代码如下：

```
#include<cstdio>
#include<algorithm>
using namespace std;

int n,a[102];
bool flag;

inline void init()
{
	register char t=getchar();
	register int x=0;
	while(t!='\n'&&t!=EOF)
	{
		if(t==',')  a[++n]=x,x=0;
		else  x=x*10+t-48;
		t=getchar();
	}
	a[++n]=x;     //最后没有逗号，需要再次更新
}
int main()
{
	init();
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;     //去重函数，并得到数组大小
	for(register int i=1;i<=n;i++)
	{
		register int j=i;
		if(flag)  printf(",");     //逗号输出细节问题
		else  flag=1;
		if(a[i+1]==a[i]+1)     //如果下一项比当前数字大1，反之亦然
		{
			while(a[j+1]==a[j]+1&&j<n)  j++;     //查找等差数列最后一项
			if(a[i]==a[j])  printf("%d",a[i]);     //如果没有等差数列则输出原数
			else  printf("%d-%d",a[i],a[j]);
		}else{
			while(a[j+1]==a[j]-1&&j<n)  j++;
			if(a[i]==a[j])  printf("%d",a[i]);
			else  printf("%d-%d",a[j],a[i]);
		}
		i=j;     //注意更新循环变量的值
	}
	return 0;
}
```

---

## 作者：PtrZ (赞：0)

## CF34C Page Numbers
[题目传送门](https://www.luogu.com.cn/problem/CF34C)

题目大意：就是给你若干个数，去重后排序，合并连续的数。

思路：那么，我们就需要进行字符串操作，如果是逗号就下一个，否则就进行跟快读一样读入数字，再利用 `map` 判断是否出现过，这就可以去重了。然后进行排序，再将差值是一的数列合并。**注意在最后是不要输出逗号**。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[500],cnt;
map<int,bool> mp;
int main(){
	string s; cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]==',') continue;
		int x=0;
		while(s[i]>='0'&&s[i]<='9'){x=x*10+s[i]-48;++i;} //处理数字
		if(!mp[x]){
			a[++cnt]=x;	
			mp[x]=true;
		} 
	}
	sort(a+1,a+cnt+1);
	//for(int i=1;i<=cnt;i++) printf("%d ",a[i]);
	for(int i=1;i<=cnt;i++){
		int k=i;
		while(a[i+1]==a[i]+1){ //合并
			i++;
		}
		if(i!=k) printf("%d-%d",a[k],a[i]);
		if(i==k) printf("%d",a[i]);
		if(i!=cnt) printf(",");
	}
	return 0;
} 
```


---

## 作者：happybob (赞：0)

这里看了看大家的代码，发现我的代码真是麻烦了……

但是我的读入根本不用字符！

没有人知道 `scanf` 可以直接存输入的东西吗？

这里看样例，都是一个整数，一个逗号，所以我们把读入写成这样：

```cpp
int x;
while (cin >> x)
{
	scanf(",");
}
```
那么最后一个逗号是没有的，怎么处理？它会读入到 `EOF`，就算没有读入逗号或者读入其他都没有关系。

然后，每次读入，加入到一个 `set` 当中，用一个迭代器去遍历，对于每一个数，往后搜索，如果当前这个数列满足条件，且下一个不满足条件，输出前面，后面。

但是最后一个数后面不用输出逗号，我采用的是把每次的答案加逗号存到一个 `string` 中，最后 `push_back` ，把最后的逗号删掉。

这题还涉及到数组传参，用指针。

代码：

```cpp
#include <iostream>
#include <string> // 用string
#include <string.h> // memset
#include <set> // set
#include <cstdio> // scanf
using namespace std;

inline bool check(int* a, int len)
{
	if (len == 1) return false;
	for (register int i = 2; i <= len; i++)
	{
		if (a[i] - a[i - 1] != 1) return false;
	}
	return true;
}

/*inline void print(int* a, int len)
{
	for (register int i = 1; i <= len; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}*/

string ans;
int a[105];

int main()
{
	set<int> st;
	int x;
	while (cin >> x)
	{
		st.insert(x);
		scanf(",");
	}
	set<int>::iterator it_end = st.end();
	for (register set<int>::iterator it = st.begin(); it != it_end; )
	{
		memset(a, 0, sizeof(a));
		set<int>::iterator it_tmp = it, new_it;
		bool flag = false;
		++it_tmp;
		int cur = 1, begin = *it, end = 0;
		a[cur] = *it;
		for (register set<int>::iterator it_2 = it_tmp; it_2 != it_end; ++it_2)
		{
			a[++cur] = *it_2;
			if (check(a, cur))
			{
				end = *it_2;
				new_it = it_2;
				flag = true;
			}
			else break;
		}
		//print(a, cur);
		if (flag)		
		{
			ans += to_string(begin) + "-" + to_string(end) + ",";
		}
		else ans += to_string(*it) + ",";
		if (flag)
		{
			it = new_it;
			++it;
		}
		else ++it;
	}
	ans.pop_back();
	cout << ans << endl;
	//system("pause");
	return 0;
}
```


---

## 作者：cbyybccbyybc (赞：0)

## 题意
给定一个数列，将其中所有的连续数字都转化成一个区间输出，即$a-b$的形式。
## Solution
现将数列从小到大排序,然后去重，从$i$开始枚举，如果是连续的，那么第$j$个的数值必定是$a_i+j-i$，如果不相等，则打断。代码如下
```cpp
//dnt为去重后的数列中数字个数
for(int i=1;i<=dnt;i++)
{
    	int f=a[i],j;
    	for(j=i+1;j<=dnt;j++)
    	{
    		if(f+j-i!=a[j]) break;
    	}
}
```
本题有几个注意点：

- 由于第$j$个是不满足的，那么要$j--$。

- 如果是第一个，在它之前不用输出$,$

- 如果$j=i$：直接输出$a_i$

- 不然输出：$a_j-a_i$

- 最后为减少时间，将$i$赋值给$j$

- 时间复杂度$O(n*logn)$即排序时长
（最后统计的看似是$O(n^2)$，但只要$j$遍历过的，$i$不用遍历，加起来其实就是$o(n)$）

- 由于$O(n*logn)$对于$n=1e6$有点卡时，最好使用快读

## 代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
int a[N],cnt=0;
bool read()
{
	char ch=getchar();
	int ans=0,f=0;
	while((ch>'9'||ch<'0')&&scanf("%c",&ch)!=EOF) ;
	while(ch>='0'&&ch<='9')
	{
		ans=ans*10+ch-'0';
		ch=getchar();
		f=1;
	}
	if(f)
	{
		a[++cnt]=ans;return 0;
	}
	else return 1;
}
signed main()
{
	while(!read());
	sort(a+1,a+cnt+1);
	int flag=0;
    int dnt=unique(a+1,a+cnt+1)-a-1;
    for(int i=1;i<=dnt;i++)
    {
    	int f=a[i],j;
    	for(j=i+1;j<=dnt;j++)
    	{
    		if(f+j-i!=a[j]) break;
    	}
    	j--;
    	if(flag!=0) cout<<",";
    	if(a[i]==a[j]) cout<<a[i];
    	else
    	cout<<a[i]<<"-"<<a[j];
    	flag++;
    	i=j;
    }
	return 0;
}
```

---

## 作者：锦瑟，华年 (赞：0)

# 本题主要思路：桶

很显然，我们只需要把数先读入，一个一个加到对应的桶中，在在最后遍历一遍，判断输出即可。接下来，我们来详细说说每部分的解决方法。

对于读入，我们可以用快读的方式读入，只不过要加一点：判断数读完之后有没有逗号，如果没有，直接退出，有的话，继续读入。

那我们怎么判断输出呢，很简单，首先，我们定义一个变量： $ans$ ，定义完之后，我们可以分以下三种情况讨论：（注：我定义的桶的数组名为 $b$ ，$i$是循环变量）

1.如果 $ans$ 并且 $b[i]!=0$ 的话，设 $ans$ 初值为1，进入下一个循环。

2.如果 $b[i-1]!=0$ 并且 $b[i]!=0$ 的话， $ans$++ 。

3.如果 $b[i-1]!=0$ 并且 $b[i]==0$的话，输出。

对于输出，我们分以下两种情况：

1.如果 $ans>1$ 的话，输出两个数 $i-ans$ 和 $i-1$。

2.如果 $ans==1$ 的话，输出 $i-1$ 。

好了，废话不多说，上代码：

	#include<stdio.h>
	using namespace std;
	int a[105],b[1005],flag[3];
	int read(){//快读
		int s=0;
		char c=getchar();
		while(c<'0'||c>'9')c=getchar();
		while(c>='0'&&c<='9'){
			s=s*10+c-'0';
			c=getchar();
		}	
		if(c!=',')flag[1]=1;//判断是否结束
		return s;
	}
	int main(){
		int i,ans=0,flag1=1;
		for(i=1;flag[1]==0;i++){//读入
			a[i]=read();
			b[a[i]]++;//桶
		}
		for(i=1;i<=1001;i++){//注意，i要遍历到1001，防止1000输出不出来的情况
			if(ans==0&&b[i]){//分类判断
				ans=1;continue;
			}
			if(b[i]&&b[i-1])ans++;
			if(b[i]==0&&b[i-1]){//输出
				if(flag1){//判断是否是第一次输出
					flag1=0;
					if(ans>1)printf("%d-%d",i-ans,i-1);//输出
					else printf("%d",i-1);
				}
				else{
					if(ans>1)printf(",%d-%d",i-ans,i-1);
					else printf(",%d",i-1);
				}
				ans=0;
			}
		}
		return 0;
	}
    
好了，大家应该都看懂了吧。题解over~~，(^_^)。

---

## 作者：fls233666 (赞：0)

此题要实现的操作较为简单，字符串长度和数字大小也不大，因此使用**模拟**解决问题。

首先，我们发现，分隔数字的符号**不是空格，是半角逗号**，**这是不能直接读入数字的**。所以我们要一个一个字符的读入，然后转换成数字。

~~写过手动读入优化的人这个应该很熟练~~。

```cpp
while(cin>>c){
if(c>='0'&&c<='9'){
	temp+=c;   //存字符串式的数字
    tnum=tnum*10+(c-'0');   //字符转换成数字
}
else{
    if(!app[tnum]){   //如果没有出现过
    	q.push(make_pair(tnum,temp));    //存下来
    	app[tnum]=1;    //标记
	}
    temp="";
    tnum=0;   //清空
}
}
```
然后准备按照题意进行模拟。

显然，我们发现。在开始模拟之前，我们要先**把数字按从小到大排序**（见样例2与样例3）。

然而我不想写sort，于是我开了优先队列......

后面是按题意模拟了。

模拟过程大概是：拿一个string标记要压缩的数列首端，一个bool标记数列长度是否$>1$，然后如果符合题意（下一个数$==$上一个数$+1$），就标记。否则根据标记情况更新答案串。最后输出答案串即可。

 _**注意：要理清程序设计的逻辑结构，执行顺序。**_ 

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<queue>
#define num pair<int,string>  //用pair包装一下
using namespace std;
bool app[1010],ca;   //app标记每个数字是否有出现
priority_queue< num , vector <num> , greater <num> >q;//优先队列（小根堆）
  
int main(){
    string ans="",temp="";  
    char c;
    int tnum=0;
    num a;
    while(cin>>c){
        if(c>='0'&&c<='9'){
            temp+=c;
            tnum=tnum*10+(c-'0');
        }
        else{
            if(!app[tnum]){
                q.push(make_pair(tnum,temp));
                app[tnum]=1;
            }
            temp="";
        	tnum=0;
        }
    }
    //创建变量与读入
                        
    if(!app[tnum]){
        q.push(make_pair(tnum,temp));
        app[tnum]=1;
    }
    //防止遗漏数字，再处理
                        
    ca=false;   
    temp=q.top().second;   //标记要压缩的数列首端
    while(!q.empty()){
    	a=q.top();   //获取堆顶
    	q.pop();   //删掉堆顶
    	if(!q.empty()&&a.first+1==q.top().first){
    		ca=true;   //标记数列长度>1
        }else{
            if(ca)   //数列长度>1
                ans+=temp+"-"+a.second+",";  //进行压缩
            else
                ans+=a.second+",";   //否则不压缩
            ca=false;  //重置
            temp=q.top().second;
        }
    }
    //压缩操作
                        
    for(int i=0;i<ans.size()-1;i++)   //输出答案，不输出最后的逗号
        putchar(ans[i]);
    return 0;
}
```


---

## 作者：MrFish (赞：0)

### 因为有去重+排序的工作，所以我们考虑使用set来做。
~~STL依赖症~~

```cpp
#include<iostream>
#include<set>

using namespace std;

int main()
{
    set<int> s;  //定义
    set<int>::iterator iter;  //定义iterator
    int a[105];
    int i=0;
    int tmp=0;
    while(true)
    {
        char ch=getchar();
        if(ch==',') 	
		{
	      s.insert(tmp);
	      tmp=0;	
		}
       else 
		{ 
			if(ch>='0'&&ch<='9')
			{
				tmp=tmp*10+ch-'0';
			}
			else 
			{
				s.insert(tmp);
				break;
			}
		}  //读入部分
    }
    i=0;
    for(iter=s.begin();iter!=s.end();iter++)
    {
	  	a[i]=*iter;
		i++;  //应为要进行后期工作，把排好序及去重了的数据放入数组中
    }
    int start=a[0];
    int ok=1;
    for(int j=0;j<i;j++)
    {
    	if(a[j]+1==a[j+1])
		{
	       ok++;
		}
		else
		{
			if(ok==1&&j!=i-1)  //非连续的，且j!=i-1
			{
				cout<<a[j]<<",";
			}
			if(ok!=1&&j!=i-1)
			{
				cout<<start<<"-"<<a[j]<<","; //连续的，且j!=i-1
			}
			if(ok==1&&j==i-1)  //非连续的，且j==i-1，不输出“，”
			{
				cout<<a[j]<<endl;
			}
			if(ok!=1&&j==i-1)
			{
				cout<<start<<"-"<<a[j]<<endl; //连续的，且j==i-1，不输出“，”
			}
			ok=1;
			start=a[j+1];
		}
   }
    return 0;  //完美
}

```



---

