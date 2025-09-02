# Santa Claus and Keyboard Check

## 题目描述

# 题义翻译
圣诞老人拆开、清洁了他的键盘，但是在将所有的按键安好后，他发现一些按键的位置发生
了两两交换！于是，圣诞老人猜测对于键盘上的每一个按键，要么在它本来正确的位置，
要么与另一个按键交换了位置。  为了验证他的猜想，他决定只根据正确的按键位置打出他
最爱的文字。现给出圣诞老人要打出的字符串 *s*，和他实际敲出的字符串 *t*,请你确定
哪几组字母发生了两两交换（即每对交换位置的字母不应出现在其他字母对中）

## 样例 #1

### 输入

```
helloworld
ehoolwlroz
```

### 输出

```
3
h e
l o
d z
```

## 样例 #2

### 输入

```
hastalavistababy
hastalavistababy
```

### 输出

```
0
```

## 样例 #3

### 输入

```
merrychristmas
christmasmerry
```

### 输出

```
-1
```

# 题解

## 作者：Patients (赞：2)

### [Santa Claus and Keyboard Check](https://www.luogu.com.cn/problem/CF748B)

------------

这……

按理说B题应该是水题，但是：

![](https://cdn.luogu.com.cn/upload/image_hosting/norsnyfu.png)

就很难受。

### 分析：

思路很简单，判断是否相同就行了。

设 $ h_i $ 表示字母 $ i $ 对应的字母。

进行分类讨论：

- $s_i=t_i$，

	+ $(h_{s_i} \ne t_i \lor h_{t_i} \ne s_i) \land (h_{s_i}\ne\varnothing \lor h_{t_i}\ne\varnothing)$，无解（即字母相同但是映射不同）。
   
   + 不然， $ h_{s_i}=t_i $ （建立映射）。

- $h_{s_i}=\varnothing \land h_{t_i}=\varnothing$，$h_{s_i}=t_i,h_{t_i}=s_i $ （双向建立映射）。

- $h_{t_i} \ne t_i \lor h_{t_i} \ne s_i $ ，无解（不同映射）。

求出各自的映射，排除了无解的情况，最后输出答案。

设 $ vis_i $ 表示字母 $ i $ 是否输出过。

遍历时，如果 $vis_{s_i}=\varnothing \land s_i \ne t_i$ ，输出（没有输出过，打标记输出）。

### Code：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
string s,t;
char h[27];
bool vis[27];
signed main()
{
#ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>s>>t;
	int ans=0;
	for(int i=0;i<=26;i++) h[i]=' ';
	for(int i=0;i<s.length();i++)
	{
		// if(s[i]==t[i]) continue ;
		if(s[i]==t[i])
			if((h[s[i]-'a']!=t[i] || h[t[i]-'a']!=s[i]) && !(h[s[i]-'a']==' ' && h[t[i]-'a']==' ')) {cout<<-1;return 0;} 
			else h[s[i]-'a']=t[i];
		else if(h[s[i]-'a']==' ' && h[t[i]-'a']==' ')
		{
			h[s[i]-'a']=t[i],h[t[i]-'a']=s[i],ans++;
			// cout<<s[i]<<' '<<t[i]<<'\n';
		}
		else if(h[s[i]-'a']!=t[i] || h[t[i]-'a']!=s[i]) {cout<<-1;return 0;} 
		// cout<<i<<' '<<h[s[i]-'a']<<'\n';
	}
	// cout<<t[1]-'a'<<'\n';
	cout<<ans<<'\n';
	for(int i=0;i<s.length();i++)
	{
		if(!vis[s[i]-'a'] && s[i]!=t[i])
		{
			vis[s[i]-'a']=vis[t[i]-'a']=1;
			cout<<s[i]<<' '<<t[i]<<'\n';
		}
	}
	return 0;
}
```

### 注意：

判断无解的顺序一定不能错，错了就挂了。

### Hack数据：

输入 1：

```
ab
aa
```
输出 1：

```
-1
```

输入 2：

```
ba
aa
```
输出 2：

```
-1
```

---

## 作者：Noby_Glds (赞：1)

这道题还挺坑的，交了我五次。
### 思路：
我们把字符串 $s$ 和 $t$ 扫一遍，用 $vis$ 数组存储字符串 $s$ 上的字符 $s(i)$ 对应字符串 $t$ 的什么字符，$kw$ 数组存储要输出的字符对。

在扫的过程中，如果 $vis(s(i))$ 和 $vis(t(i))$ 都没赋值，那么 $vis(s(i))$ 等于 $t(i)$ 且 $vis(t(i))$ 等于 $s(i)$。

因为 $kw$ 数组存储的字符对里的两个字符是不同的，所以仅当 $s(i)$ 不等于 $t(i)$ 时，才将它们存入 $kw$ 数组。

如果 $vis(s(i))$ 或 $vis(t(i))$ 被赋值了，且 $vis(s(i))$ 不等于 $t(i)$ 或 $vis(t(i))$ 不等于 $s(i)$，就输出 $-1$，结束程序。

最后输出 $kw$ 数组的所有字符对就可以啦。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;   //我把s换成了a，t换成了b。
int vis[150],kw[1500],tot;
int main(){
	cin>>a>>b;
	for(int i=0;i<a.size();i++){
		if(vis[a[i]]==0&&vis[b[i]]==0){
			vis[a[i]]=b[i];
			vis[b[i]]=a[i];
			if(a[i]!=b[i]) kw[++tot]=a[i];
			continue;
		}
		if((vis[a[i]]!=b[i]||vis[b[i]]!=a[i])){
			cout<<"-1";
			return 0;
		}
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++){
		char x,y;
		x=kw[i];
		y=vis[x];   //输出时要从int类型转为char。
		cout<<x<<" "<<y<<endl;
	}
	return 0;
}
```
$\texttt{286ms}$，还挺快。

---

## 作者：Zaku (赞：0)

这是一题简单模拟题，难度大约在橙。
#### 题意：
就是问有几组对应关系，并输出。

给一组例子：```ab``` 和 ```aa```。

在这组例子里，a 先和 a 对应，然后 a 又和 b 对应，说明对应关系出错了，所以答案应该输出 $-1$。
#### 解题思路：
声明一个数组 ```check```，用于建立起 $s$ 和 $t$ 的对应关系，挨个判断字符合不合规（是否有且只有一个字符与其对应）。若不合规，直接输出 $-1$；若合规，就扫描一下数组统计需要交换的次数，再打印解决方案。

详细解释见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,int> check;//用来记录两个字符交换的信息
int main(){
    string s,t;cin>>s>>t;
    int len=s.size();
    for(int i=0;i<len;i++){
        if(!check[s[i]] or !check[t[i]]){//如果这两个字符还没有被对应
            if(!check[s[i]] and !check[t[i]]){//判断是否已经有一个字符被对应
                check[s[i]]=t[i];//都没被对应，就记录下对应关系 
                check[t[i]]=s[i];
            }else{//否则输出-1 
                cout<<-1<<endl;
                return 0;
            }
        }else{
            if(check[s[i]]!=t[i] or check[t[i]]!=s[i]){//两个字符不匹配就输出-1
                cout<<-1<<endl;
                return 0;
            }
        }	
	}
    int ans=0;          
    for(int i='a';i<='z';i++)
        if(check[i]>i)ans++;//按字典序遍历一遍，查找ans个数 
    cout<<ans<<endl;
    for(int i='a';i<='z';i++)//极富美感地按字典序输出答案 
        if(check[i]>i)cout<<(char)i<<" "<<(char)check[i]<<endl;
    return 0; 
}
```


---

## 作者：Ninelife_Cat (赞：0)

转换一下思路，我们可以把两个字母交换位置看作在它们中间连了一条无向边，那么最后得到的就是若干个连通块。

如果某个连通块中元素个数大于 $2$，意味着至少有一个字母对应两个及以上的字母，这样显然是不合法的，边做边判即可。

最后在输出的时候把自环去掉就行了。

核心代码：

```cpp
string s,t;
int len,siz;
vector<pair<char,char> > ans;
map<char,char> a;//存字母的对应关系
signed main()
{
	cin>>s>>t;len=s.size();
	for(ri int i=0;i<len;++i)
	{
		if(a[s[i]]&&a[s[i]]!=t[i]) return cout<<-1,0;
		if(a[t[i]]&&a[t[i]]!=s[i]) return cout<<-1,0;//一个字母对应多个字母时无解
		if(!a[s[i]]&&!a[t[i]]) ans.pb(mp(s[i],t[i])),a[s[i]]=t[i],a[t[i]]=s[i];
	}
	siz=ans.size();
	for(ri int i=0;i<ans.size();++i)
		if(ans[i].fir==ans[i].sec) --siz;//去除自环
	cout<<siz<<endl;
	for(ri int i=0;i<ans.size();++i)
		if(ans[i].fir!=ans[i].sec) cout<<ans[i].fir<<" "<<ans[i].sec<<endl;
	return 0;
}
```

---

