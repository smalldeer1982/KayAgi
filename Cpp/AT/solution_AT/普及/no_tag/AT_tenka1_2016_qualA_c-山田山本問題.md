# 山田山本問題

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2016-quala/tasks/tenka1_2016_qualA_c

天下一株式会社に勤務するワタナベくんは、社内のコミュニケーションにチャットツールを使っています。 チャットツールには補完機能があり、@で始まるアカウント名を入力しようとすると、プレフィックスの一致するアカウント名の一覧を辞書順で補完候補として表示してくれます。

ところが、ワタナベくんは補完候補の中から @yamamoto を選ぼうとした時に、間違って @yamada を選択してしまうことが多々あります。 @yamada は @yamamoto より辞書順で小さく、 `@yama` まで入力した際に、候補の先頭に表示されてしまうためです。

ワタナベくんは不思議な特技を持っていて、アルファベットの順番を自由に並べ替えることができます。 例えば、ワタナベくんが特技を使ってアルファベットの順番を abcefghijklmdnopqrstuvwxyz にすると、 `m` は `d` より小さくなり、 @yamamoto を @yamada より辞書順で小さくすることができます。

アカウント名 $ A_i $ をアカウント名 $ B_i $ より辞書順で小さくしたいという要求が $ N $ 個与えられます。 与えられた要求をすべて満たすような、ワタナベくんの特技によって並べ替えられたアルファベットの順番を求めてください。 条件を満たすようなアルファベットの順番が複数存在する場合は、並べ替えられる前のアルファベットの順番での辞書順最小の順番を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ A_i\ \neq\ B_i $
- $ 1\ \leq\ |A_i|,\ |B_i|\ \leq\ 1000 $
- $ A_i,B_i $は英小文字で構成される

## 样例 #1

### 输入

```
1
yamamoto yamada```

### 输出

```
abcefghijklmdnopqrstuvwxyz```

## 样例 #2

### 输入

```
3
xx xy
z w
v w```

### 输出

```
abcdefghijklmnopqrstuvxyzw```

## 样例 #3

### 输入

```
2
a b
b a```

### 输出

```
-1```

## 样例 #4

### 输入

```
1
yamamoto yama```

### 输出

```
-1```

# 题解

## 作者：This_Rrhar (赞：6)

~~你谷题目爬虫玩xx玩多了？~~

第一个样例可能会让人有点懵：`yamamoto` 怎么可能会 `yamada` 呢？实际上这题比较时要用 `string` 的默认比较方式，也就是把两个字符串**左对齐**，然后从左到右地比较字符大小！但是人类通常会先用字符串的**长度**来决定大小，当长度相等时才会进行上述过程。

考虑怎么解决问题。如果我们已知字符间的大小，则可以建一张图，将小的字符向大的字符连边，再进行拓扑排序即可。如果拓扑排序不成功，则说明要求的字符偏序集不存在，输出 $\texttt{-1}$。

那么对于输入的字符串 $s,t$，首先要找到第一个下标 $k$ 使得 $s_k\ne t_k$：

- 如果找得到，则连边 $s_k\to t_k$。

- 如果找不到且 $s$ 的长度大于 $t$，那么显然不存在任何一个字符偏序集满足 $s<t$，直接输出 $\texttt{-1}$ 即可。

注意这样可能会存在重边，所以在修改入度时要小心。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define V 26

priority_queue<ll,vector<ll>,greater<ll>>q;
bool G[V][V];
ll deg[V];
string ans;
void tpsort()
{
	for(int i=0;i<V;i++)if(!deg[i])q.push(i);
	while(!q.empty())
	{
		ll u=q.top();
		q.pop(),ans+=char(u+'a');
		for(int i=0;i<V;i++)if(G[u][i]&&!--deg[i])q.push(i);
	}
}

ll n;

string s,t;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	while(n--)
	{
		cin>>s>>t;
		bool dif=false;
		for(size_t i=0;i<min(s.size(),t.size());i++)
			if((s[i]-='a')!=(t[i]-='a'))
			{
				deg[t[i]]+=!G[s[i]][t[i]],G[s[i]][t[i]]=dif=true;
				break;
			}
		if(!dif&&s.size()>=t.size())return cout<<"-1\n",0;
	}
	tpsort();
	if(ans.size()==26)cout<<ans<<"\n";
	else cout<<"-1\n";
}
```

---

## 作者：Autumn_Rain (赞：4)

### 温馨提示

此题解并非拓扑排序且为无代码题解，或许是篇贪心？仅仅分享蒟蒻晚修摸鱼出来的一种解法，内含正确性证明。并且与本人的拓扑排序进行过答案比较，均正确。如有漏洞请及时联系我进行更改或补充说明，那么我们开始吧！

### 非法判断

先从简单的非法方案入手。不难发现非法情况有两种，一种是第二个字符串是第一个的前缀，此时第一个字符串字典序一定大于第二个。这种情况考虑直接扫一遍判断。

第二种是相互冲突，比如在先前操作中，一个字符的字典序已确定小于另一字符。但在接下来的操作中，它又变成字典序大于那个字符的了。这种情况可以用并查集解决。

### 引理

对于一组字符串的处理，我们只需处理一对字符串最先不同的那个位置即可，其他对结果无影响。

字符一在字符二之前，这里的字符指原字符串经过第一步处理后的得到的字符。这个过程可理解为字符二插到字符一后面。

插到字符一后面的字符的原字典序小于字符一。

### 思路分析

从现在开始我们将字符串转换为单个字符再转换为数字，因此以下我称这些字符为数。这里我们需要准备一个栈和一个队列维护最终字母表。注意，此处的循环顺序对结果影响很大，因此先别急着质疑操作正确性，这个等会会证明。

我们要完成以下三个操作，每一个操作基于两个数字：

- 操作一：若第一个数在队列中的位置比第二个数字更前，那么无需理会即为最优解。

- 操作二：如果要本插入此数后方的数在先前操作中已经插入到了此数的后面位置，无需理会。

- 操作三：向一个数后面插数时，我们优先插在原字典序中较小的数再插较大的。

最后得到的队列即为最终字母表。

### 实践操作

虽然古人云：OI 证明全靠猜，但我们还是提一下证明过程。

这里是[关于操作一二的证明](https://www.luogu.com.cn/paste/hbi0kj5e)呀！

循环顺序很耐人寻味，我们采用二维布尔数组存储有没有插与被插的关系，伪代码如下。

```cpp
for(int i=26;i>=1;i--){//1到26代表a到z这26个字母
	for(int i=1;i<=26;i++){
    	if(!a[i][j])continue;
        if(非法方案)continue;
        else 执行操作三; 
    }        
    /*例子：对于输入：
    6
    d a
    t l
    o v
    e c
    j x
    t a
    它的处理顺序应该是（当然这当中有一些不用处理）
    t a
    t l
    o v
    j x
    e c
    d a*/
}
```

为什么这么做呢？不妨思考一下这个问题，你把一些数字插到了一个数字后面，可是这个数字又插到了别的数字后面，那岂不是得拖家带口全部搬走？为了避免这个清况，我们先插最后的数字，再依次枚举往前，一定可以避免此类情况，[这里是证明](https://www.luogu.com.cn/paste/x3daovqj)。

关于我们操作一的实现还有一个有意思的事，就是当我们想把数字一插入数字二后面时，当然，这里的后面指数字二的最后一个插数后面。只需弹出队列的数字二减一个数然后再入队。为什么永远是数字二减一个呢？[证明在这里呀](https://www.luogu.com.cn/paste/z8tr974q)。

### 总结

做这道题，我们需要一个栈，一个队列，一个并查集，一个二维数组，还有一颗没有被烧坏的脑子。我的这种方法应该不会太难实现，但是思维上有一点点跳脱了，比起简洁明了的拓扑排序貌似并没有什么好处，甚至我一开始也是奔着拓扑排序来做这题的。但是多一种方法又何尝不好呢？毕竟这才是 OI 的乐趣嘛。

---

## 作者：封禁用户 (赞：1)

拓扑排序，将每组字符串按位比较连边，如果后一个字符串是前一个字符串的前缀，输出 -1。最后使用小根堆拓扑排序，如果有环输出 -1，否则输出整个拓扑排序的结果。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> G[30];
char top[30];
int r[30];
void top_sort(){
	int tot=0;
	priority_queue<int,vector<int>,greater<int> > q;
	for(int i=0;i<26;++i){
        if(!r[i]) q.push(i);
    }
	while(!q.empty()){
        int tmp=q.top();
        q.pop();
        top[++tot]=tmp+'a';
        for(auto i:G[tmp]){
            --r[i];
            if(!r[i]) q.push(i);
        }
    }
    if(tot!=26){
    	cout<<-1<<endl;
    	return ;
	}
	for(int i=1;i<=26;++i){
		cout<<top[i];
	}cout<<endl;
	return ;
}
signed main(){
	int tt;
	string s,t;
	cin>>tt;
	bool f=0;
	while(tt--){
		cin>>s>>t;
		int n=min(s.size(),t.size());
		f=0;
		for(int i=0;i<n;++i){
			if(s[i]!=t[i]){
				G[s[i]-'a'].push_back(t[i]-'a');
				++r[t[i]-'a'];
				f=1;
				break;
			}
		}
		if(f==1) continue;
		if(s.size()>t.size()){
			cout<<-1<<endl;
			return 0;
		} 
	}
	top_sort();
	return 0;
}
```

---

## 作者：Lyx8058 (赞：1)

## 大佬请跳过本篇题解。

## 标签/难度：
拓扑排序、字符串（入门）。

橙题，因为这题纯纯拓扑排序模板题。
## 思路：
### 壹：
对于每一组字符串，从左到右依次枚举字符，若字符出现不同，那么就要使得第一个字符序列定义的大小 **恒大于** 第二个字符。

- 那如果一直模拟到等于呢？

对于这个，我们可以举例说明，出题人非常良心地给了我们样例 #4 ：

```
1
yamamoto yama
```

仔细观察不难发现，如果一直枚举到等于，那么如果左侧的字符串长度大于右侧的字符串长度，那么由蒟蒻的智慧可得，左边的字典序恒大于右侧字典序，直接输出 ```-1``` 
。
### 贰：
现在就可以建图了，可以采用链式前向星或者邻接表存储，我们可以知道，当要字符字典序小于另一个字符，则要保证该字符的输出顺序早于另一个字符，所以建图时是由第一个指向第二个。

接下来就没什么好说的，直接拓扑。
### 叁：
当看到题目中的“如果满足条件的字母表序列有多种，输出值最小的序列。”时，我们可以发现大根堆可以直接帮助我们存储答案。

这题坑点不多，但是要仔细甄别。

## Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=30;
int n,in[N];
vector<int>e[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		string x,y;
		cin>>x>>y;
		int f=0;
		int xy_length=min(x.length(),y.length());//取两字符串最小长度，方便比较。  
		for(int j=0;j<xy_length;j++){
			if(x[j]!=y[j])//不同就连图  
			{
				e[int(x[j]-'a'+1)].push_back(int(y[j]-'a'+1));//建图  
				in[int(y[j]-'a'+1)]++;//入度++  
				f=1;
				break;//由于当前的位置是两字符串字符不同的最小下标位置，所以后续怎么的大小都不重要。  
			}
		}
		if(!f){//一直一样的字符  
			if(x.length()>y.length()){//恒大于  
				cout<<"-1\n";//原地击毙 ！  
				return 0;
			}
		}
	}
	
	/* 拓扑 */
	
	priority_queue<int,vector<int>,greater<int>> q;//大根堆  
	
	for(int i=1;i<=26;i++){//入度为零就入队  
		if(in[i]==0) q.push(i);
	}
	int ans[N],ans_length=0;//存储答案  
	while(!q.empty()){
		int u=q.top();
		ans[++ans_length]=u;
		q.pop();
		for(auto k:e[u]){
			if(--in[k]==0) q.push(k); //删除当前边，如果入度为零就将字符入队。  
		}
	}
	if(ans_length!=26){//如果没有达到26个字符都计入了答案  
		cout<<"-1\n";
		return 0;
	}
	for(int i=1;i<=ans_length;i++){
		cout<<char(ans[i]+'a'-1);
	}
	cout<<"\n";//好习惯 *1 
	return 0;//好习惯 *2 
}//圆满结束！！！ 
```


## 华丽的结尾：
![](https://fecdn.luogu.com.cn/luogu/ac-congrats.png?ce96b99faabe0d91e25e00917ef494af)

---

