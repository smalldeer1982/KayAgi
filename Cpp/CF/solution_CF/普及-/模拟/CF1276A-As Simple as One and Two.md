# As Simple as One and Two

## 题目描述

You are given a non-empty string $ s=s_1s_2\dots s_n $ , which consists only of lowercase Latin letters. Polycarp does not like a string if it contains at least one string "one" or at least one string "two" (or both at the same time) as a substring. In other words, Polycarp does not like the string $ s $ if there is an integer $ j $ ( $ 1 \le j \le n-2 $ ), that $ s_{j}s_{j+1}s_{j+2}= $ "one" or $ s_{j}s_{j+1}s_{j+2}= $ "two".

For example:

- Polycarp does not like strings "oneee", "ontwow", "twone" and "oneonetwo" (they all have at least one substring "one" or "two"),
- Polycarp likes strings "oonnee", "twwwo" and "twnoe" (they have no substrings "one" and "two").

Polycarp wants to select a certain set of indices (positions) and remove all letters on these positions. All removals are made at the same time.

For example, if the string looks like $ s= $ "onetwone", then if Polycarp selects two indices $ 3 $ and $ 6 $ , then "onetwone" will be selected and the result is "ontwne".

What is the minimum number of indices (positions) that Polycarp needs to select to make the string liked? What should these positions be?

## 说明/提示

In the first example, answers are:

- "onetwone",
- "testme" — Polycarp likes it, there is nothing to remove,
- "oneoneone",
- "twotwo".

In the second example, answers are:

- "onetwonetwooneooonetwooo",
- "two",
- "one",
- "twooooo",
- "ttttwo",
- "ttwwoo" — Polycarp likes it, there is nothing to remove,
- "ooone",
- "onnne" — Polycarp likes it, there is nothing to remove,
- "oneeeee",
- "oneeeeeeetwooooo".

## 样例 #1

### 输入

```
4
onetwone
testme
oneoneone
twotwo
```

### 输出

```
2
6 3
0

3
4 1 7 
2
1 4
```

## 样例 #2

### 输入

```
10
onetwonetwooneooonetwooo
two
one
twooooo
ttttwo
ttwwoo
ooone
onnne
oneeeee
oneeeeeeetwooooo
```

### 输出

```
6
18 11 12 1 6 21 
1
1 
1
3 
1
2 
1
6 
0

1
4 
0

1
1 
2
1 11 
```

# 题解

## 作者：vectorwyx (赞：3)

贪心

从左往右遍历字符串，如果碰到了 `one`，那就把中间的 `n` 删去，这样不可能产生新的 `one`。

如果碰到了 `two`，那就再看一下后面的两个字符。如果是 `twone` 那就删 `o`，否则删 `w`。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=2e6+5;
string s; 
int ans[N],top;

void work(){
	cin>>s;
	top=0;
	int n=s.size();
	fo(i,0,n-3){
		if(s[i]=='o'&&s[i+1]=='n'&&s[i+2]=='e'){
			//printf("%d\n",i);
			ans[++top]=i+1;
			i+=2;
		}
		else if(s[i]=='t'&&s[i+1]=='w'&&s[i+2]=='o'){
			if(s[i+3]=='o') ans[++top]=i+1;
			else ans[++top]=i+2;
			i+=2;
		}
	}
	cout<<top<<endl;
	fo(i,1,top) printf("%d ",ans[i]+1);puts("");
	//puts("");
}

int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：安舒阳 (赞：1)

本题是半道贪心。

既然要贪，怎么贪最好呢？当然是让每个删除的字符发挥它最大的价值，要一次根治、一刀斩断、杜绝后患。

我们不难发现，对于一个单独的 `one` 只需删去一个字符即可使它不成立。上面说到要杜绝后患，怎么样能最大限度地杜绝呢？**我在这个子串前面放上什么、后面放上什么都不会使得这个子串“死灰复燃”就可以算作最大限度**了吧？

分情况讨论：

1. 删除字母 `o`，在这种情况下我只需在前面的字串中包含一个不属于子串的 `o` 即可，并不符合要求。
2. 删除字母 `e`，同理上文我们可以发现，只需在后方添加一个相同字母就可以再次得到 `one`，并不符合要求。
3. 删除字母 `n`，这样一来得到 `oe`，就不可能再产生一个新的 `one` 了，问题解决。

对于 `two` 也是一样的，删除 `w` 即可，在此不再赘述。

**但是**，这里有个特例 `twone` 在这种情况下两个子串共用了字母 `o`，不论删除 `w` 还是删除 `n` 都会导致另外一方依旧成立，这时删除字母 `o` 即可，因为它的两侧都被两个字符“保护”着，不存在会“死灰复燃”的可能。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int q;
	scanf("%d",&q);
	while(q--){
		int ans=0;
		vector<int> num;
		string s;
		cin>>s;
		
		for(int i=2;i<s.size();i++){
			//one
			if(s[i]=='e'&&s[i-1]=='n'&&s[i-2]=='o'){
				ans++;
				num.push_back(i-1);
			}
			
			//two
			if(s[i]=='o'&&s[i-1]=='w'&&s[i-2]=='t'){
				ans++;
				//twone
				bool flag=1;
				if(i+2<s.size()){
					if(s[i+1]=='n'&&s[i+2]=='e'){
						num.push_back(i);
						flag=0;
						i+=2;
					}
				}
				//twoXXX
				if(flag){
					num.push_back(i-1);
				}
			}
		}
		printf("%d\n",ans);
		for(int i=0;i<num.size();i++){
			printf("%d ",num[i]+1);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：rsjw (赞：1)

~~又水了一题~~

**这里直接判断字符串是否相等就好了，还要注意一个细节:当连续字符为:"twone"时应删除"o",其他情况下不能删"o"**

**(因为包括"twooooooooone"的情况)**

~~SPJ太烦人了~~


```cpp
#include <bits/stdc++.h>
using namespace std;
char a[150010];
int step[150010],k;
int main() {
#ifdef DEBUG
	freopen("1.in","r",stdin);
#endif
	int n;
	scanf("%d",&n);
	while(n--) {
		k=0;
		scanf("%s",a+1);
		int l=strlen(a+1)-2;
		for(int i=1; i<=l; i++) {
			if(a[i]=='o'&&a[i+1]=='n'&&a[i+2]=='e') a[i+1]='z',step[++k]=i+1;
			else if(a[i]=='t'&&a[i+1]=='w'&&a[i+2]=='o') {
				if(a[i+3]=='o') a[i+1]='z',step[++k]=i+1;
				else a[i+2]='z',step[++k]=i+2;
			}
		}
		printf("%d\n",k);
		for(int i=k; i>=1; i--) printf("%d ",step[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Sky_exe (赞：0)

粗略读一下题，看起来很难，似乎要搜索。

## **但是！！**

其实可以分类讨论一下:

字符串中会出现3种情况:

如果是 $\verb!one!$ 此时可以删除 $\verb!n!$ 来解决。

```cpp
if(s[i] == 'o'&&s[i+1] == 'n' && s[i+2] == 'e')
{
	ans++;
	del[ans] = i+1+1;//再加一是因为输出从1开始，下标+1
	s[i+1] = '3';
}
```


如果是 $\verb!two!$ 但后面不是 $\verb!ne!$ 时可以删除 $\verb!o!$ 来解决。

如果是 $\verb!twone!$ 只能删除 $\verb!o!$ 来解决。

```cpp
if(s[i] == 't' && s[i+1] == 'w' && s[i+2] == 'o')
{
	ans++;//不论是情况3还是情况2都要删去一个字符，+1
 	if(s[i+3] == 'n'&&s[i+4] == 'e')//如果是情况3
	{
		del[ans] = i+2+1;
		s[i+2] = '3';
	}
	else//不是情况3就是情况2
	{
		del[ans] = i+1+1;
		s[i+1] = '3';
	}
}
```

为什么不能无脑删除呢?

看一下这个例子: $\verb!oonee!$

如果删除一个 $\verb!o!$ 那么会变成: $\verb!onee!$ ，里面依然有 $\verb!one!$。

如果删除一个 $\verb!e!$ 变成 $\verb!oone!$ ，里面也有 $\verb!one!$。

$\verb!two!$ 也是一样的，都只能删除中间的字符。

至于 $\verb!twone!$ 只有将2者共用的 $\verb!o!$ 删除才可以。

$\verb!tone!$ 和 $\verb!twoe!$ 等删除其他字符的都不行。


------------


## **AC Code**:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
const int maxn = 2e5+5;
int del[maxn];
int ans = 0;
int readint()
{
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch))
    {
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}
signed main()
{
    //freopen("one_and_two.in","r",stdin);
    //freopen("one_and_two.out","w",stdout);
    int T;
    T = readint();
    while(T--)
    {
        memset(del,0,sizeof(del));
        cin>>s;
        ans = 0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i] == 'o'&&s[i+1] == 'n' && s[i+2] == 'e')
            {
                ans++;
                del[ans] = i+1+1;
                s[i+1] = '3';
                //i+=3;
            }
            if(s[i] == 't' && s[i+1] == 'w' && s[i+2] == 'o')
            {
                ans++;
                if(s[i+3] == 'n'&&s[i+4] == 'e')
                {
                    del[ans] = i+2+1;
                    s[i+2] = '3';
                }
                else
                {
                    del[ans] = i+1+1;
                    s[i+1] = '3';
                }
            }
        }
        printf("%lld\n",ans);
        if(ans == 0)
        {
            puts("");
        }
        else
        {
            for(int i=1;i<=ans;i++)
            {
                printf("%lld ",del[i]);
            }
            puts("");
        }
    }
}
```


---

## 作者：gyh20 (赞：0)

贪心。

如果找到一个 $one$ 那么删去中间的 $n$ 一定是最佳的。

如果是 $two$ 那么如果是 $twone$ 的情况，删去 $o$ 可以保证少删一个数，否则删去 $w$ 来保证准确性。

代码:
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<map>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
int pos[150002],num;
char s[150002];
int main(){
	int t,n;
	scanf("%d",&t);
	while(t--){
		scanf("%s",s+1);
		n=strlen(s+1);
		num=0;
		for(re int i=1;i<=n-2;++i){
			if(s[i]=='o'&&s[i+1]=='n'&&s[i+2]=='e')pos[++num]=i+1,s[i]='a';
			if(s[i]=='t'&&s[i+1]=='w'&&s[i+2]=='o')if(s[i+3]=='o'&&i<=n-3)pos[++num]=i+1;else pos[++num]=i+2,s[i+2]='a';
		}
		printf("%d\n",num);
		for(re int i=1;i<=num;++i)printf("%d ",pos[i]);
	//	printf("%s\n",s+1);
		putchar('\n');
	}
}
```


---

## 作者：Meatherm (赞：0)

分类讨论，且优先级从上到下：

- `twone`。删除 `o` 即可，变为 `twne`。
- `two`。删除 `w` 即可，变为 `to`。
- `one`。删除 `n` 即可，变为 `oe`。

于是扫 $3$ 遍字符串。使用 `std::string` 和其成员函数  `find()` 可以有效的降低代码量。


--- 
简单介绍一下 `find()`。`x.find(y,z)` 返回 `x` 中从 `y` 开始字符串 `z` 第一次出现的位置，查找不到则返回 `std::string::npos`，这个值通常为 $-1$，但是为了平台兼容性建议写做前者。

例如当 a=`abcabc` 时：

- `a.find(0,abc)` 返回值是 $0$。
- `a.find(2,abc)` 返回值是 $3$。
- `a.find(1,abc)` 返回值是 `std::string::npos`。


```cpp
# include <bits/stdc++.h>
# define rr register

const int N=1500010;

std::string x;
int T;
int Queue[N];
int main(void){
	scanf("%d",&T);
	while(T--){
		std::cin>>x;
		int cnt=0;
		int st=0,res;
		do{
			res=x.find("twone",st);
			if(res==std::string::npos)
				break;
			++cnt;
			x[res+2]='.';
			Queue[cnt]=res+2;
			st=res+1;	
		}while(res!=std::string::npos);
		st=0;
		do{
			res=x.find("one",st);
			if(res==std::string::npos)
				break;
			++cnt;
			x[res+1]='.';
			Queue[cnt]=res+1;
			st=res+1;	
		}while(res!=std::string::npos);
		st=0;
		do{
			res=x.find("two",st);
			if(res==std::string::npos)
				break;
			++cnt;
			x[res+2]='.';
			Queue[cnt]=res+1;
			st=res+1;	
		}while(res!=std::string::npos);	
		printf("%d\n",cnt);	
		for(rr int i=1;i<=cnt;++i){
			printf("%d ",Queue[i]+1);//因为题目中下标从 1 开始，但程序中为 0
		}
		puts("");
	}	
	
	return 0;
}
```

---

## 作者：woshishei (赞：0)

这道题的大意是给定一些字符串，删除一些字符使字符串中不出现 `one` 或 `two` 作为连续子串，并且删除的字符数量最小。

一共考虑这几种情况：

- `one` 单独出现时，删掉任意一个字符即可。

- `o...oone` 或 `onee...e` 或 `o...oonee...e` 时（`n` 的左右分别有一个或多个 `o` 和 `e`），删掉中间的 `n` 即可。

- `w` 的左右分别有一个或多个 `t` 和 `o` 时，删掉中间的 `w` 即可。

- 当出现 `two` 后面的 `o` 和 `ne` 相连时，需要分类讨论：

  - 只有一个 `o`，即 `twone` 时，删掉中间的 `o`；
  
  - 有多个 `o` 时，最好删掉前面的 `w`（因为 `t` 可能有多个连续的），和后面的 `n`。

所以总共只有可能删除三种字符：`o`、`n` 和 `w`。分情况讨论即可。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
char s[150010];
int len,ans[150010],sum;
void solve()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	sum=0;
	int pos=1;//记录当前处理字符的位置
	while(pos<=len)
	{
		if(s[pos]!='t'&&s[pos]!='o')//如果不是two或one的开头字母，直接跳过
		{
			pos++;
			continue;
		}
		if(s[pos]=='t'&&s[pos+1]=='w'&&s[pos+2]=='o')//two的情况
			if(pos+2==len)//已经到头
			{
				ans[++sum]=pos+2;
				pos++;
			}
			else if(s[pos+3]=='n')//如果是twon...就直接删除o
			{
				ans[++sum]=pos+2;
				s[pos+2]=' ';
				pos+=4;
			}
			else//否则删除w
			{
				ans[++sum]=pos+1;
				s[pos+1]=' ';
				pos+=2;
			}
		else if(s[pos]=='o'&&s[pos+1]=='n'&&s[pos+2]=='e')//one的情况，直接删除n，twone的情况已经考虑过，所以不用再分类讨论
		{
			ans[++sum]=pos+1;
			s[pos+1]=' ';
			pos+=3;
		}
		else
			pos++;
	}
	printf("%d\n",sum);
	for(int i=1;i<=sum;i++)
		printf("%d ",ans[i]);//输出方案
	printf("\n");
	for(int i=1;i<=len;i++)//出于恶心的数据范围，不能直接memset，但如果用string就没有这样的问题
		s[i]=0;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：YuanZihan1225 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1276A)

# 题意分析

我们能够很轻易的想到贪心，让我们来分析一下方案：

## one ：
显然，删掉 n 是最佳方案，例如： ooone 和 oneeee 就不能先删 o 和 e 。

## two ：
此时，我们就要考虑两种情况：

1. 如果是 twone 既有 two 又有 one ，我们就应直接删去 o ，而不是分别删去。

2. 否则就直接删掉 w，原因与 one 差不多，一面有后面的的字母补上来。

## 记录方案:
这就比较简单了，有各种各样的方法，我采用 STL 大法： vector ！~~（主要是因为我太懒了）~~

# 代码见下：

```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
string s;
int n, t, sum = 0;
signed main()
{
	cin >> t;
	while(t--)
	{
		vector<int> ans;
		cin >> s;
		n = s.size(), sum = 0;
		for(int i = 0; i < n; i++)
		{
			if(s[i] == 'o' && s[i + 1] == 'n' && s[i + 2] == 'e')
				ans.push_back(i + 2), i += 2;//把答案塞进去，同时注意要跳过已经被处理过的
			else if(s[i] == 't' && s[i + 1] == 'w' && s[i + 2] == 'o')
			{
				if(s[i + 3] == 'n' && s[i + 4] == 'e')
					ans.push_back(i + 3), i += 4;
				else
					ans.push_back(i + 2), i += 2;
			}
		}
		int l = ans.size();//输出答案
		cout << l << endl;
		for(int i = 0; i < l; i++)
			cout << ans[i] << " ";
		cout << endl;
	}
	return 0;//完美的结束QWQ
}
```

---

