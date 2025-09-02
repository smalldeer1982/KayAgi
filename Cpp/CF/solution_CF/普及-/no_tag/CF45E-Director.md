# Director

## 题目描述

给出$n$个名字和$n$个附名，请你将名字和附名两两配对，使得首字母相同的名字对数最多，并以最小字典序输出。

## 样例 #1

### 输入

```
4
Ann
Anna
Sabrina
John
Petrov
Ivanova
Stoltz
Abacaba
```

### 输出

```
Ann Abacaba, Anna Ivanova, John Petrov, Sabrina Stoltz```

## 样例 #2

### 输入

```
4
Aa
Ab
Ac
Ba
Ad
Ae
Bb
Bc
```

### 输出

```
Aa Ad, Ab Ae, Ac Bb, Ba Bc```

# 题解

## 作者：Mars_Dingdang (赞：14)

~~楼上好像有一点点问题~~……$so$ 本蒟蒻来发题解啦~

### 题目内容
这道题乍一看是考察字符串的题，但其实远没有那么简单……

给出 $n$ 个名字和 $n$ 个附名，请你将名字和附名两两配对，使得**首字母相同**的名字对数最多，并以**最小字典序**输出。

### 大体思路
这道题不仅要按字典序排序，还要按首字母配对。首先是按字典序排序。排序部分还是很简单的，只要用`sort`函数即可（快速排序）。

用法：包含在 `algorithm` 头文件中。

**$sort$(起始地址，结束地址+1，排序规则），其中排序规则可省略，默认为从小到大（如本题）。**

代码如下：
```cpp
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n[i];//输入name
	}
	for(int i=1;i<=t;i++){
		cin>>s[i];//输入Surname
	}
	sort(n+1,n+t+1);
	sort(s+1,s+t+1);//快速排序
```
接下来的部分才是关键：即**按首字母配对**。

首先记录首字母（记录到数组 $la,lb$ 中）。接下来进行搜索，条件为当一个 $Surname$ 未被使用时，如果首字母相同且按字典序，就记录下来，并将其标记为已使用。最后输出即可。

代码如下：
```cpp
for(int i=1;i<=t;i++){
		la[n[i][0]]++;
		lb[s[i][0]]++;
	}//待满足的首字母
	for(int i=1;i<=t;i++){
		int tmp;
		for(int j=1;j<=t;j++){
			if(flag[j]==0 && (la[s[j][0]]<lb[s[j][0]] || n[i][0]==s[j][0]) && (lb[n[i][0]]<la[n[i][0]] || s[j][0]>=n[i][0]))
			{
				tmp=j;
				break;
			}
		}//搜索
		same[i]=tmp;//记录配对
		flag[tmp]=1;//标记为已使用
		lb[s[tmp][0]]--;
		la[n[i][0]]--;//删除这一对
	}
	for(int i=1;i<=t;i++){
		cout<<n[i]<<" "<<s[same[i]];//配对输出
		if(i!=t) cout<<", ";
	}//输出（不要多一个逗号）
```

### 完整AC代码：
```cpp
#include<iostream>
#include<string>
#include<algorithm>//排序头文件
using namespace std;
string n[102];
string s[102];
int same[102],la[102],lb[102];
bool ？？？//删掉标记数组防作弊
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n[i];
	}
	for(int i=1;i<=t;i++){
		cin>>s[i];
	}//输入不做解释
	sort(n+1,n+t+1);
	sort(s+1,s+t+1);//排序
	for(int i=1;i<=t;i++){
		la[n[i][0]]++;
		lb[s[i][0]]++;
	}//记录
	for(int i=1;i<=t;i++){
		int tmp;
		for(int j=1;j<=t;j++){
			if(flag[j]==0 && (la[s[j][0]]<lb[s[j][0]] || n[i][0]==s[j][0]) && (lb[n[i][0]]<la[n[i][0]] || s[j][0]>=n[i][0]))
			{
				tmp=j;
				break;
			}//搜索
		}
		same[i]=tmp;//配对
		flag[tmp]=1;//标记已使用
		lb[s[tmp][0]]--;
		la[n[i][0]]--;
	}
	for(int i=1;i<=t;i++){
		cout<<n[i]<<" "<<s[same[i]];
		if(i!=t) cout<<", ";
	}//配对输出
	return 0;//完美
}
```
~~看得这么认真，不点个赞再走嘛qaq~~

---

## 作者：lrx___ (赞：2)

**思路**

要以最小字典序输出，我们将这些字符串排序即可。

要使首字母相同的对数最多，我们直接枚举并判断即可。

**代码**

```cpp
#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=105;
string a[N],b[N];
int c[35],d[35],e[N];
bool v[N];
/* 数组 a,b 存储输入的字符串 */
/* 数组 c,d 存储输入字符串首字母出现的个数 */
/* 数组 e 记录答案 */
/* 数组 v 记录是否使用过 */
int main(){
	int n,i,j;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		cin>>a[i];
		c[(int)(a[i][0]-'a')]++;
	}
	for(i=0;i<n;i++){
		cin>>b[i];
		d[(int)(b[i][0]-'a')]++;
	}
	sort(a,a+n),sort(b,b+n);
/*	使用 sort 进行排序 */
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(!v[j]&&(c[(int)(b[j][0]-'a')]<d[(int)(b[j][0]-'a')]||a[i][0]==b[j][0])&&(d[(int)(a[i][0]-'a')]<c[(int)(a[i][0]-'a')]||b[j][0]>=a[i][0])){
				e[i]=j;
				v[j]=1;
				c[(int)(a[i][0]-'a')]--;
				d[(int)(b[j][0]-'a')]--;
				break;
			}
		}
	}
	for(i=0;i<n;i++){
		printf("%s %s",a[i].data(),b[e[i]].data());
/*		string.data() 功能可以将 string 类型转换为 const char* 类型，这样就可以用 printf 进行输出啦 */
		if(i<n-1){
			printf(", ");
/*			特判是否为最后 */
		}
	}
	return 0;
}
```

**小知识**

`string.data()`功能可以将`string`类型转为`const char*`类型，就可以使用`printf`输出啦。

---

## 作者：ChenZQ (赞：2)

首先是看字典序。

我们直接给两个字符串数组排序。

然后我们可以建两个一维数组来统计首字母出现的次数。

每次遍历一个名称字符串，如果首字母相同就直接配上，标记一下后退出循环。如果发现配不上，我们可以看一下当前字符串的首字母有没有空闲。**意思就是说当前字符串能不能按首字母两两配对之后空闲下来**。如果是空闲的，就直接匹配上然后标记退出循环。

时间复杂度为 $O(n^2)$ 可以通过此题。

具体实现方法看代码。


```
#include <bits/stdc++.h>
using namespace std;

string n[100010];
string s[100010];
int same[102],la[102],lb[102];
bool flag[100010];

int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++) cin>>n[i],la[n[i][0]]++;
	for(int i=1;i<=t;i++) cin>>s[i],lb[s[i][0]]++;//统计首字母。
	sort(n+1,n+t+1);//排序。
	sort(s+1,s+t+1);
	for(int i=1;i<=t;i++)
	{
		int tmp;
		for(int j=1;j<=t;j++)
		{
			if(flag[j]==0 && (la[s[j][0]]<lb[s[j][0]] || n[i][0]==s[j][0]) && (lb[n[i][0]]<la[n[i][0]] || s[j][0]>=n[i][0]))//首先就是判断有没有被用过，其次就是看首字母是不是相同的或者当前字符串空闲了。
			{
				tmp=j;
				break;
			}
		}
		same[i]=tmp;
		flag[tmp]=1;//配对。
		lb[s[tmp][0]]--;
		la[n[i][0]]--;//当前已匹配，删除掉。
	}
	for(int i=1;i<=t;i++){
		cout<<n[i]<<" "<<s[same[i]];
		if(i!=t) cout<<", ";//注意末尾没有逗号。
	}
}
```

---

## 作者：qzhwmjb (赞：2)

#### 思路
利用两个二维数组分别记录名字和附名.   
因为是按字典序来的，所以可以使用sort.   
再利用两个数组记录所需和拥有的量.  
循环判断名字和附名是否匹配.   
匹配--》记录.  
所需和拥有量都减1.  
匹配要求：   
```cpp
c[b[j][0]]<d[b[j][0]]||a[i][0]==b[j][0]
d[a[i][0]]<c[a[i][0]]||b[j][0]>=a[i][0]
```

循环输出结果.  
注意点：  
因为第一个匹配名字不需要输出逗号 .  
所以要特殊处理.  
循环也要从第二个开始.
### 全代码
---
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[500],b[500];
int i,n,j,k;
int with[500],use[500],c[500],d[500];
int main(){
    cin>>n; 
    for(i=1;i<=n;i++){
      cin>>a[i];
      c[a[i][0]]++;
    }     
    for(i=1;i<=n;i++){
      cin>>b[i];
      d[b[i][0]]++;
	  } 
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    j=1;
    k=1;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
	    if(use[j]==0){
               if((c[b[j][0]]<d[b[j][0]]||a[i][0]==b[j][0])){
                  if(d[a[i][0]]<c[a[i][0]]||b[j][0]>=a[i][0]){
                		break;
					}
				}
        	}
		} 
    	with[i]=j;
        use[j]=1;
        d[b[j][0]]--;
        c[a[i][0]]--;
    }
    cout<<a[1]<<" "<<b[with[1]];
    for(i=2;i<=n;i++){
    	cout<<", "<<a[i]<<" "<<b[with[i]];
    }
    return 0;
}
```

---

## 作者：Sun_wtup (赞：1)

# Director 题解
[题目传送](https://www.luogu.com.cn/problem/CF45E)

~~究竟是我太菜还是题目太抽象~~
## 题意
给出 $n$ 个名字和 $n$ 个附名，要求将他们两两配对即一个名字，一个附名配成一对，使得首字母相同的名字对数最多，并且字典序最小。
## 分析与思路
这就是一道字符串的题目。统计名字和附名中每种首字母出现次数，然后将名字和附名拍一下序，对于每一个名字找符合要求的与其配对，然后记录一下，最后输出即可
## 实现
重点看名字与附名的配对部分。想配对成功，要满足两个要求。
  - 名字的首字母在所有附名的首字母中出现的次数要小于在名字中出现的次数或者附名的首字母大于等于名字的首字母。
  - 附名的首字母在所有名字首字母中出现的次数要小于在附名中出现的次数或者名字和附名的首字母相同。
  
只要这两个要求满足就配对成功了。

补充：用来存首字母次数时没有用数组，为了保险用了 `map<char,int>mps;` 存次数，当然数组也不会炸，但是还是希望不会的同学自学一下，毕竟他真的很好用~~虽然占空间有点大~~。

最后不要忘记：不能出现额外的空格或者逗号。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl
string s[105];
string a[105];
bool af[105];
struct node {
    string f;
    string s;
    string sum;
}p[105];
map<char,int>mps;
map<char,int>mpa;
int cnt;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        mps[s[i][0]]++;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mpa[a[i][0]]++;
    }
    sort(s+1,s+1+n);
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        p[i].f=s[i];
        int flag;
        for(int j=1;j<=n;j++){
            if(af[j])continue;
            if(mpa[s[i][0]]<mps[s[i][0]] or a[j][0]>=s[i][0]){
                if(mps[a[j][0]]<mpa[a[j][0]] or a[j][0]==s[i][0]){
                    flag=j;
                    break;
                }
            }
        }
        af[flag]=1;
        p[i].s=a[flag];
        mps[s[i][0]]--;
        mpa[a[flag][0]]--;
    }
    for(int i=1;i<=n;i++){
        cout<<p[i].f<<" "<<p[i].s;
        if(i!=n)cout<<", ";
    }
    return 0;
}
```
本蒟蒻水平有限，如有不周之处，请见谅。

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Director](https://www.luogu.com.cn/problem/CF45E)

### 注意事项

本题要用 sort，不会的同学可以[点这里](https://blog.csdn.net/VariatioZbw/article/details/125155432)。

## 算法思路

首先记录首字母（记录到数组 $cnta$，$cntb$ 中）。接下来进行搜索，条件为当一个附名未被使用时，如果首字母相同且按字典序，就记录下来，并将其标记为已使用。最后输出即可。

### 样例讲解

当配对为 Ann 配 Abacaba，Anna 配 Ivanova，John 配 Petrov，Sabrina 配 Stoltz 时，首字母相同的名字对数最多，而且的最小字典序。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long
const ll N=110;
ll n,cnta[N],cntb[N],same[N],ans;
string a[N],b[N];
bool vis[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		cnta[(ll)a[i][0]]++;//累加
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		cntb[(ll)b[i][0]]++;//累加
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		ans=0;
		for(int j=1;j<=n;j++)
		{
			if(!vis[j]&&(cnta[(ll)b[j][0]]<cntb[(ll)b[j][0]]||a[i][0]==b[j][0])&&(cntb[(ll)a[i][0]]<cnta[(ll)a[i][0]]||b[j][0]>=a[i][0]))
			//如果没用过，而且满足条件 
			{
				ans=j;
				break;
			}
		}
		vis[ans]=true;//标记用过 
		cnta[(ll)a[i][0]]--;//次数-- 
		cntb[(ll)b[ans][0]]--;//次数-- 
		same[i]=ans;//存答案 
	}
	for(int i=1;i<=n;i++)//输出 
	{
		cout<<a[i]<<" "<<b[same[i]];
		if(i!=n)
		{
			cout<<", ";
		}
	}
	cout<<"\n";//我习惯换行 
	return 0;
}
```


---

## 作者：pengzy___ (赞：0)

### 题意：

给出 n 个名字和 n 个附名，请你将名字和附名两两配对，使得首字母相同的名字对数最多，并以最小字典序输出。

### 思路：

输入代码：
```cpp
cin>>n;
for(int i=1;i<=n;i++)
    cin>>a[i];
for(int i=1;i<=n;i++)
    cin>>b[i];
```

首先，这道题不仅要把名字和附名两两匹配，还要按字典序进行从小到大的排序。

字典序排序只要用 STL 库函数 sort 快速排序即可。

快速排序代码：
```cpp
sort(a+1,a+1+n);
sort(b+1,b+1+n);
```

因为循环输入的时候数组下标是从 1 开始的，所以排序时上下标都要加 1 。sort 函数默认是从小到大排序，所以不用再写排序的顺序。

按首字母匹配时需要用到三个数组，两个一维数组用来记录名字和附名的首字母，一个 bool 型的用来标记。

记录名字和附名的代码：
```cpp
int a_s[105],b_s[105];
    for(int i=1;i<=n;i++) {
        a_s[a[i][0]]++;
        b_s[b[i][0]]++;
    }
```

在输入的时候也是可以记录的。

接下来，就是判断首字母了。如果匹配成功，需要用 bool 数组标记为已使用，并记录到一个统计 same 的数组中。

搜索判断首字母、统计答案的代码：
```cpp
bool f[105];
    int same[105];
    for(int i=1;i<=n;i++) {
        int cmp;
        for(int j=1;j<=n;j++) 
            if(f[j]==0&&(a_s[b[j][0]]<b_s[b[j][0]]||a[i][0]==b[j][0])&&(b_s[n[i][0]]<a_s[n[i][0]]||b[j][0]>=a[i][0]))
            {
                cmp=j;
                break;
            }
        same[i]=cmp;
        f[cmp]=1;
        b_s[b[cmp][0]]--;
        a_s[a[i][0]]--;
    }
```

输出代码：
```cpp
for(int i=1;i<=n;i++) {
        cout<<a[i]<<' '<<b[same[i]];
        if(i!=n)cout<<", ";
    }
```

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[105],b[105];
int n,a_s[105],b_s[105],same[105];
bool f[105];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) {
        a_s[a[i][0]]++;
        cin>>a[i];
    }
    for(int i=1;i<=n;i++) {
        b_s[b[i][0]]++;
        cin>>b[i];
    }
    sort(a+1,a+1+n);
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++) {
        int cmp;
        for(int j=1;j<=n;j++) 
            if(f[j]==0&&(a_s[b[j][0]]<b_s[b[j][0]]||a[i][0]==b[j][0])&&(b_s[n[i][0]]<a_s[n[i][0]]||b[j][0]>=a[i][0]))
            {
                cmp=j;
                break;
            }
        same[i]=cmp;
        f[cmp]=1;
        b_s[b[cmp][0]]--;
        a_s[a[i][0]]--;
    }
    for(int i=1;i<=n;i++) {
        cout<<a[i]<<' '<<b[same[i]];
        if(i!=n)cout<<", ";
    }
    return 0;
}
```


---

## 作者：Tobiichi_Origami (赞：0)

**这是一道字符串**

**题目大意**

输入 $n$ 个名字和 $n$ 个姓，把名字和姓配对，使得姓与名首字母相同的对数最多，按字典序输出。

**大体思路**

题目中说要按字典序输出，所以我们就先在输入的时候排序，可以用 $\texttt{algorithm}$ 库中的 $\texttt{sort}$ 函数来排序。

然后再用两个数组来记录名字和姓，一个 $\texttt{bool}$ 数组来标记。

之后就是判断是否合法，如果 $\texttt{bool}$ 数组标记为 $1$ 而且首字母匹配，那就标记为 $0$，将记录名字和姓的数组各自 $-1$，用一个 $\texttt{name}$ 数组来统计答案。

最后输出，切记最后一个没有逗号。

**贴代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string a[101],b[101];
int aa[101],bb[101],name[101];
bool vis[101];
int n;//定义数组变量
int main()
{
    memset(vis,1,sizeof(vis));//个人习惯
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];//输入
    for(int i=1;i<=n;i++)
    {
        aa[(int)a[i][0]]++;
        bb[(int)b[i][0]]++;
    }//记录名字和姓
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);//字典序排序
    for(int i=1;i<=n;i++)
    {
        int j;
        for(j=1;j<=n;j++)//搜索
        {
            if(vis[j]&&(bb[(int)a[i][0]]<aa[(int)a[i][0]]||b[j][0]>=a[i][0])&&(aa[(int)b[j][0]]<bb[(int)b[j][0]]||a[i][0]==b[j][0]))
            //未被使用并且首字母匹配
                break;
        }
        name[i]=j;//记录
        vis[j]=0;//标记
        aa[(int)a[i][0]]--;
        bb[(int)b[j][0]]--;//删除这一对名字和姓
    }
    for(int i=1;i<=n;i++)
    {
        cout<<a[i]<<" "<<b[name[i]];//输出
        if(i==n) return 0;//少一个逗号
        cout<<", ";
    }
    return 0;//华丽的结束
}
```



---

