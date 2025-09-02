# Beautiful String

## 题目描述

### 题意简述

给定字符串 $s$，由 `a`，`b`，`c`，`?` 四种字符构成。

您需要将 $s$ 中的所有 `?` 修改为 `a`，`b`，`c` 中的一种，使得 $s$ 相邻两个字符均不相同。

## 样例 #1

### 输入

```
3
a???cb
a??bbc
a?b?c
```

### 输出

```
ababcb
-1
acbac
```

# 题解

## 作者：Aybbl_xc (赞：2)

# 前言
这是本蒟蒻的~~第二篇题解~~。（准确来说是第三篇，因为第二篇没过审）
# 题目大意
给定字符串，由 `a`,`b`,`c`,`?` 四种字符构成。您需要将 
所有 `?` 修改为 `a`,`b`,`c` 中的一种，使得相邻两个字符均不相同。无解输出 $-1$。（其实题目很好理解）
# 思路
- 我首先可以先找是否有相邻且相等的字符串但不能是 `?`，接着标记直接退出。
- 处理问号我们直接模拟，把所有可能都列出来，要判断前后是否相等，如果不懂就直接看代码吧。

# 代码环节

```
#include<bits/stdc++.h>
using namespace std;
bool flag; /*标记*/
int n;
string s;
char cmp(int k){//模拟答案
	if(k-1==-1){
		if(s[k+1]=='a')return 'b';
		if(s[k+1]=='b')return 'c';
		if(s[k+1]=='c')return 'a';
		return 'a';
	}
	if(s[k-1]=='a'){
		if(s[k+1]=='b')return 'c';
		if(s[k+1]=='c')return 'b';
		return 'c';
	}
	if(s[k-1]=='b'){
		if(s[k+1]=='a')return 'c';
		if(s[k+1]=='c')return 'a';
		return 'a';
	}
	if(s[k-1]=='c'){
		if(s[k+1]=='a')return 'b';
		if(s[k+1]=='b')return 'a';
		return 'b';
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		flag=false;//重置标记 
		cin>>s;
		int l=s.size();//记录长度 
		for(int i=1;i<l;i++){
			if(s[i]==s[i-1]&&s[i]!='?'){//判断是否相等 
				flag=true;
				break;
			}
		}
		if(flag==true){//如果重复直接退出 
			cout<<-1<<endl;
			continue;
		}
		for(int i=0;i<l;i++){//直接模拟 
			if(s[i]=='?') s[i]=cmp(i);//把所有情况枚举一遍 
		}
		cout<<s<<endl;
	}
	return 0;//好习惯！！！ 
}
```
# [AC记录](https://www.luogu.com.cn/record/122338695)
完结散花！！！
望管理大大能给过


---

## 作者：Cappuccino_mjj (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1265A)
题目意思：

给你一个带有 ``a``、``b``、``c``、``?`` 这些字符的字符串。你可以吧 ``?`` 改成 ``a``、``b`` 或 ``c``。要求改完的字符串相邻的字符不能相同。

---

思路：
1. 先判断当前字符串是否合法。
2. 如果合法就直接模拟任意一个答案即可。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a;
bool f()
{//判断合法
	for(int i=1;i<a.size();i++)
		if(a[i]==a[i-1]&&a[i]!='?')
			return true;
	return false;
}
char calc(int id)
{//模拟答案
	if(id-1==-1)
	{
		if(a[id+1]=='a')return 'b';
		if(a[id+1]=='b')return 'c';
		if(a[id+1]=='c')return 'a';
		return 'a';
	}
	if(a[id-1]=='a')
	{
		if(a[id+1]=='b')return 'c';
		if(a[id+1]=='c')return 'b';
		return 'c';
	}
	if(a[id-1]=='b')
	{
		if(a[id+1]=='a')return 'c';
		if(a[id+1]=='c')return 'a';
		return 'a';
	}
	if(a[id-1]=='c')
	{
		if(a[id+1]=='a')return 'b';
		if(a[id+1]=='b')return 'a';
		return 'b';
	}
}
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>a;
		if(f())
		{//判断是否合法
			cout<<-1<<endl;
			continue;
		}
		for(int i=0;i<a.size();i++)
		{
			if(a[i]=='?')
			{
				a[i]=calc(i);//模拟任意一个答案
			}
		}
		cout<<a<<endl;
	}
	return 0;
}
```

---

完美撒花~

---

## 作者：Soaring_light (赞：1)

### 题意
给定字符串 `s`，由 `a`，`b`，`c`，`?` 四种字符构成。

需要将 `s` 中的所有 `?` 修改为 `a`，`b`，`c` 中的一种，使得 `s` 相邻两个字符均不相同。

观察样例不难发现，**只要原字符串没有连续两个相同字符，就一定有解**，我们只需要判断原字符串是否合法，再遍历字符串即可。

一些具体做法在注释里，代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,opt;//opt标记此轮是否输出过-1
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>s;
		opt=0;
		for(int j=0;j<=s.length()-1;j++){
			if(j!=0 && s[j]==s[j-1] && s[j]!='?'){
				cout<<-1<<endl;
				opt=1;break;
			}else//判断字符串是否合法
				if(s[j]=='?'){
					if(j==0){
						if(s[j+1]=='a')s[j]='b';
						else s[j]='a';
					}
					if(j==s.length()-1 || (j<=s.length()-2 && s[j+1]=='?')){
						if(s[j-1]=='a')s[j]='b';
						else s[j]='a';
					}//下一位已有字符则选择与前后都不相同的字符
					if(j<=s.length()-2 && s[j+1]!='?'){
						if(s[j-1] == s[j+1]){
							if(s[j-1]=='a')s[j]='b';
							else s[j]='a';
						}else
							for(int l=0;l<=2;l++){
								s[j]=char(l+int('a'));
								if(s[j]!=s[j-1] && s[j]!=s[j+1])
								break;
							}
                //否则选择与前一位不同的字符
                //这里我选择尽量用字典序小的字符，减小偶然性
					}
				}
		}
		if(opt==0)
		cout<<s<<endl;
	}
	return 0;
}
```
第一次写题解，希望多多包涵。


---

## 作者：Meatherm (赞：1)

如果原字符串的第 $i$ 位不是 `?`，那么不能更改，跳过。

否则在 `a`，`b`，`c` 三种里面选一种填。由于第 $i-1$ 位和第 $i+1$ 位至多会出现两种不同的字符所以一定有解。特殊的，如果第 $i+1$ 位也是 `?`，那么就只需要满足和 $i-1$ 位不同。

最后扫描字符串，如果发现非法就输出 `NO`，否则就是合法的。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=100010;
char s[N];
int T;
int n;
bool use[10];
int main(void){
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);
		n=strlen(s+1);
		for(rr int i=1;i<=n;++i){
			if(s[i]!='?')
				continue;
			memset(use,false,sizeof(use));
			if(i>1)
				use[s[i-1]-'a'+1]=true;
			if(i<n&&s[i+1]!='?')
				use[s[i+1]-'a'+1]=true;	
			for(rr int j=1;j<=3;++j){
				if(!use[j]){
					s[i]='a'+j-1;
					break;
				}
			}
		}
		for(rr int i=1;i<n;++i){
			if(s[i]==s[i+1]){
				puts("-1");
				goto End;
			}
		}
		puts(s+1);
		End:;
	}
	return 0;
}
```

---

## 作者：Ar_cher (赞：0)

字符串基础题

**题意概述：**给定一串只包含 `a`、`b`、`c`、`?` 的字符串 $s$，其中 `?` 可以替换成 `a`/`b`/`c`，要求两两不同，输出这个字符或 `-1`。

**思路：**可以枚举，但我觉得要找找技巧。我们只需要把把 `?` 的前后的字符改变就可以了，但注意我们要 $\%3$，因为有前后和本身共 $3$ 个数。

**代码如下：**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,i;
string s;
signed main(){
	cin>>T;
	while(T--){
		cin>>s;
		int x=0,cnt=0;
		int len=s.length();
		for(i=0;i<len;i++){//字符长度一般都从0开始 
			if(s[i]==s[i+1] and s[i]!='?') break;
			else if(s[i]=='?'){//不能写成else 
				while(s[i]==s[i+1] or s[i]==s[i-1] or s[i]=='?'){
					s[i]=cnt%3+'a';//这里的%3是指i-1,i,i+1三个下标对应的数
					cnt++;
				} 
			}
		}
		if(len>i) cout<<-1<<endl;
		else cout<<s<<endl;
	}
	return 0;
} 
```

若您觉得写得好，请点个赞，谢谢！

---

## 作者：zwyyy (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1265A)

---

## 思路
由于修改后的字符串 $s$ 只由 `a`，`b`，`c` 三种字符构成，所以只要不是题目原本给出的字符串无解就一定有解。推导出这条结论后我们的代码就可以变得更加简洁。

## 具体实现
1. 输入字符串；
2. 判断是否有解，无解直接输出 `-1`，回到第一步；
3. 枚举所有 `?` 所在的位置，并判断 `?` 能替换成哪个字符
4. 直接输出，注意不要忘记有多组数据。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1005][100005];
char find(int x, int y){
	int n[3] = {0};
	if(s[x][y - 1] == 'a' || s[x][y + 1] == 'a')	n[0] = 1;
	if(s[x][y - 1] == 'b' || s[x][y + 1] == 'b')	n[1] = 1;
	if(s[x][y - 1] == 'c' || s[x][y + 1] == 'c')	n[2] = 1;
	if(n[0] != 1)	return 'a';
	if(n[1] != 1)	return 'b';
	if(n[2] != 1)	return 'c';
}
int main(){
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i){
		int flag = 0;
		scanf("%s", s[i]);
		char last = '0';
		int len = strlen(s[i]);
		for(int j = 0; j < len; ++j){
			if(s[i][j] == '?'){
				last = '0';
				continue;
			}
			if(s[i][j] == last){
				printf("-1\n");
				flag = 1;
				break;
			}
			last = s[i][j];
		}
		if(flag == 1){
			continue;
		}
		for(int j = 0; j < len; ++j){
			if(s[i][j] == '?'){
				if(j == 0){
					if(s[i][1] == 'a'){
						s[i][0] = 'b';
					}
					else{
						s[i][0] = 'a';
					}
				}
				else if(j == len - 1){
					if(s[i][len - 2] == 'a'){
						s[i][j] = 'b';
					}
					else{
						s[i][j] = 'a';
					}
				}
				else{
					s[i][j] = find(i, j);
				}
			}
		}
		printf("%s\n", s[i]);
	}
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/121295767)

---

## 作者：封禁用户 (赞：0)

第一次写题解！

题意：

给定字符串 $s$，由  ```a```，```b```，```c```，```?```  四种字符构成。

您需要将 $s$ 中的所有 ```?``` 修改为 ```a```，```b```，```c``` 中的一种，使得 $s$ 相邻两个字符均不相同。

思路：

如果这个字符串的第 $i$ 位不是  ```?```，这能说明这字符串没有解，直接输出  $-1$;反之在  ```a```，```b```，``c`` 中任选一个，因为 第 $i$ 位 与第 $i+1$ 位字符串最多有 $2$ 个不同字符，定有解。

最后扫描一下字符串，按以上思路判断一下字符串是否有解，即可。

代码：

```
 int n;
    scanf("%d", &n);
    while (n--) {
        int flag = 1; //这个是用来标记这个字母（a-c）中的其中一个字母是否想相邻
        scanf("%s", s + 1);//细节
        int l = strlen(s + 1);//l就相当于字符串的长度
        for (int i = 1; i <= l; i++) {
            if (s[i] != '?' && s[i + 1] == s[i]) {
                flag = 0; 
                break;
            }
        }
        if (!flag)//如果没有符合要求的字符串
            printf("-1\n"); 
        else {
            for (int i = 1; i <= l; i++) {
                if (s[i] != '?') {
                    printf("%c", s[i]); 
                } else {
                    int pos1 = i;
                    int pos2 = 0;
                    for (i = i; i <= l; i++) {
                        if (s[i + 1] != '?') {
                            pos2 = i; 
                            break;
                        }
                    }
                    solve(pos1, pos2); 
                }
            }
            printf("\n");
        }
    }
    return 0;
}
```


---

## 作者：czxQQQ (赞：0)

第一次写题解！！！

## 思路

这题的思路很简单，首先遍历字符串，如果是 `?` 就开始分两种情况判断。

$1.$ 如果 $i-1$ 和 $i+1$ 都不是 `?`，那么就有唯一的答案。因为题目说字符串里只有 `a`,`b`,`c`,`?` 四种可能。
 
$2.$ 如果 $i+1$ 是 `?`，那么只要做到 $i \neq i+1$ 就行了。因为题目有说如果有多组解，输出**任意一组**就行了。

只要考虑到这两点。这题就很好解决了。

然后注意特判一下 `s.length()` $=1$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
void f(char &a,char &b,char &c){ 
	if(a=='a'&&b=='a') c='b';
	if(a=='b'&&b=='b') c='a';
	if(a=='c'&&b=='c') c='a';
	if(a=='a'&&b=='b'||a=='b'&&b=='a') c='c';
	if(a=='a'&&b=='c'||a=='c'&&b=='a') c='b';
	if(a=='b'&&b=='c'||a=='c'&&b=='b') c='a';
}
int main(){
	int n,t;
	string a;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		t=0;
		if(a.length()==1){//特判只有一个字符的情况 
			if(a[0]=='?'){cout<<"a\n";continue;}
			else{cout<<a<<"\n";continue;}
		}
		for(int j=0;j<a.length();j++){
			if(a[j]=='?'){
				if(j==0){//特判边界 
					if(a[j+1]=='?') a[j]='a';
					if(a[j+1]=='a') a[j]='b';
					if(a[j+1]=='b'||a[j+1]=='c') a[j]='a';
				}
				else if(j==a.length()-1){//特判边界
					if(a[j-1]=='a') a[j]='b';
					if(a[j-1]=='b'||a[j-1]=='c') a[j]='a';
				}
				else if(a[j-1]!='?'&&a[j+1]!='?') f(a[j-1],a[j+1],a[j]);//左右两边都不是?的情况 
				else if(a[j+1]=='?'){//右边是?的情况 
					if(a[j-1]=='a') a[j]='b';
					if(a[j-1]=='b'||a[j-1]=='c') a[j]='a';
				}
			}
		}
		for(int j=0;j<a.length()-1;j++){//还要判断一下是否输出-1 
			if(a[j]==a[j+1]){cout<<"-1\n";t=1;break;}
		}
		if(t==0) cout<<a<<"\n";
	}
	return 0;
}
```

---

## 作者：lmndiscyhyzdxss (赞：0)

## 题意
给定字符串 $ s $，由```a```，```b```，```c```，```?```四种字符构成。

您需要将 $ s $ 中的所有```?```修改为```a```，```b```，```c```中的一种，使得 $ s $ 相邻两个字符均不相同。
## 分析
如果该位置不是问号，改不了。
否则在```a```，```b```，```c```三种里面选一种填。如果 $ i+1 $ 和 $ i-1 $ 位都以给定，直接取另外那个，如果 $ i+1 $ 位为```?```，直接取跟第 $ i-1 $ 为不同的且最小的那个就可以了，这个过程可以用数组计数实现，用是```s[i]-'a'+1```作为下标，最后还要判断两个相邻的字母是否不同。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,p,bl[10];
string s;
int main()
{
	cin>>t;
	for(int z=1;z<=t;z++)
	{
		cin>>s,p=1,l=s.size();
		for(int i=0;i<l;i++)
		{
			if(s[i]!='?')continue;
			else
			{
				bl[1]=0,bl[2]=0,bl[3]=0;
				if(i>0)bl[s[i-1]-'a'+1]++;
			    if(i<l-1&&s[i+1]!='?')bl[s[i+1]-'a'+1]++;	
			    for(int j=1;j<=3;j++)
				{
				    if(bl[j]==0){s[i]='a'+j-1;break;}
			    }
			}
		}
		for(int i=0;i<l;i++)
		{
			if(s[i]==s[i+1]){cout<<"-1"<<endl,p=0;break;}
		}
		if(p==1)cout<<s<<endl;
	}
	return 0;
}
```

---

## 作者：LBYYSM_123 (赞：0)

### 思路
设字符串为 $s$。  
首先**只要**判断是 `?` 的字符，接下来在 `a`,`b`,`c` 里选一种，由于第  $s_{i-1}$ 位和第 $s_{i+1}$ 位最多只会出现两种不同的字符所以一定有解。  
**注意**：如果 $s_{i+1}$ 为 `?`，那么 $s_{i+1} \neq s_{i-1}$。   
最后判断一下合不合法就可以了。
### Code
```cpp
#include<bits/stdc++.h>
#define add_(i) (++i) 
#define dec_(j) (--j)
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t,lens;string s;
	cin>>t;
	do{
		bool *n=(bool*)malloc(4*sizeof(bool));
		cin>>s;
		lens=s.size();
		for(int i=0;i<lens;add_(i)){
			if(s[i]=='?'){
				memset(n,0,sizeof(n));
				if(i>0) n[s[i-1]-96]=1;
				if(i<lens-1&&s[i+1]!='?') n[s[i+1]-96]=1;
				for(int j=1;j<=3;add_(j))
					if(n[j]==0){
						s[i]=j+96;
						break;
					}
			}
		} 
		for(int i=0;i<lens;add_(i))
			if(s[i]==s[i+1]){
				cout<<"-1\n";
				goto end;
			}
		cout<<s<<'\n';
		end:free(n);
	}while(dec_(t),t>0);
	return 0;
} 
```

---

## 作者：czrjx (赞：0)

## 题意

给出一个由 `a`，`b`，`c`，`?` 组成的字符串，要求把 `?` 改成 `a`，`b`，`c` 其中之一，并且相邻两个字符不能重复。

## 思路

先考虑无解的情况：如果一位是 `?`，那它的相邻位最多只能是 `a`，`b`，`c` 其中两个，肯定可以将它改成相邻两位中没有出现的那一位，所以只有当给出的原字符串中有相邻位的字符相同时才会出现无解。

对于一个有解的字符串中的出现 `?`，只需要用 `a`，`b`，`c` 依次和它相邻两位比对，若与相邻两位均不相同则可以将这位上的字符固定下来。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char b[10]={'a','b','c'};
int main()
{
	string s;
	int n,i,j,k;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>s;
		int f=0;
		for(j=0;j<s.size();j++)
		{
			if(s[j]!='?'&&s[j]==s[j+1])		//判断是否有解
				f=1;
		}
		if(f==1)
		{
			cout<<-1<<endl;
			continue;
		}
		for(j=0;j<s.size();j++)
		{
			if(s[j]=='?')
			{
				for(k=0;k<3;k++)
					if(b[k]!=s[j-1]&&b[k]!=s[j+1])
						s[j]=b[k];
			}
		}
		cout<<s<<endl;
	}
}
```


---

