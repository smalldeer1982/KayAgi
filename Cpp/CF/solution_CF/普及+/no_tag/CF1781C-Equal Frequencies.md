# Equal Frequencies

## 题目描述

Let's call a string balanced if all characters that are present in it appear the same number of times. For example, "coder", "appall", and "ttttttt" are balanced, while "wowwow" and "codeforces" are not.

You are given a string $ s $ of length $ n $ consisting of lowercase English letters. Find a balanced string $ t $ of the same length $ n $ consisting of lowercase English letters that is different from the string $ s $ in as few positions as possible. In other words, the number of indices $ i $ such that $ s_i \ne t_i $ should be as small as possible.

## 说明/提示

In the first test case, the given string "hello" is not balanced: letters 'h', 'e', and 'o' appear in it once, while letter 'l' appears twice. On the other hand, string "helno" is balanced: five distinct letters are present in it, and each of them appears exactly once. Strings "hello" and "helno" differ in just one position: the fourth character. Other solutions are possible too.

In the second test case, string "codefofced" is balanced since only letters 'c', 'o', 'd', 'e', and 'f' are present in it, and each of them appears exactly twice.

In the third test case, string "eeeee" is balanced since only letter 'e' is present in it.

In the fourth test case, the given string "appall" is already balanced.

## 样例 #1

### 输入

```
4
5
hello
10
codeforces
5
eevee
6
appall```

### 输出

```
1
helno
2
codefofced
1
eeeee
0
appall```

# 题解

## 作者：daiarineko (赞：11)

# 题解【CF1781C Equal Frequencies】

## 0. 题意

给出长度为 $n$ 的只包含小写字母的字符串 $s$，请修改尽量少的字符，使得每种出现过的字符出现次数相同。给出最优的修改次数和一种方案。（一定有解）

## 1. 思路

首先，为了让每种字符出现次数相同，字母个数 $k$ 必然为 $n$ 的因数（显然地，$k\leq 26$，否则字符不够用）。

枚举可能的 $k$，此时可以求出最少的修改次数：我们将每个字母的出现次数排序，保留出现次数最多的 $k$ 种字母，而剩余的字母去除。

这相当于，前 $k$ 种字母出现次数为 $\frac{n}{k}$，其余的为 $0$。求出每种字母实际出现次数和目标的差距之和并除以 $2$，即为最少的修改次数。（为什么要除以 $2$？因为每次修改可以改变两个字母的出现次数。）

继而，根据以上的求法，我们也得到了一种最优解的构造：每次修改将（实际出现次数）超过目标的字母“分配”给低于目标的字母，具体见代码。

## 2. 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s;
int cnt[26];
struct Node
{
    int id, cnt;
} v[26];
bool cmp(Node a, Node b)
{
    return a.cnt > b.cnt;
}
signed main()
{
    int t;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n >> s;
        fill(cnt, cnt + 26, 0);
        for (int i = 0; i < s.length(); ++i)
            ++cnt[s[i] - 'a'];
        int ans = 0x3f3f3f3f3f3f3f3fll, ansid = 0;
        for (int i = 0; i < 26; ++i)
            v[i] = {i, cnt[i]}; // 记录出现次数
        sort(v, v + 26, cmp); // 排序
        for (int used = 1; used <= 26; ++used)
        { // 枚举使用的字母个数 k
            if (n % used != 0)
                continue;
            int m = n / used; // n / k
            int now = 0;
            for (int i = 0; i < used; ++i)
                now += abs(v[i].cnt - m); // 前 k 个字母的目标为 n / k
            for (int i = used; i < 26; ++i)
                now += v[i].cnt; // 剩余字母的目标为 0
            now /= 2; // 每次修改可以改变 2 个出现次数
            ans = min(ans, now);
            if (ans == now)
                ansid = used;
        }
        cout << ans << '\n'; // 先输出修改次数，下面进行构造
        for (int i = 0; i < ansid; ++i)
            cnt[v[i].id] = n / ansid;
        for (int i = ansid; i < 26; ++i)
            cnt[v[i].id] = 0; // 保存目标出现次数
        for (int i = 0; i < s.length(); ++i)
        {
            bool vis = false;
            for (int j = 0; j < ansid; ++j)
                if (v[j].id == s[i] - 'a')
                {
                    vis = true;
                    break;
                } // 判断当前字母可不可以保留
            if (!vis)
                s[i] = '\0'; // 因为当前字母不在前 k 种里，所以不能保留
            else if (cnt[s[i] - 'a'])
                --cnt[s[i] - 'a'];
            else
                s[i] = '\0'; // 因为当前字母出现次数过多，所以不能保留
        }
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] != '\0')
                continue; // 对不能保留的字母重新分配
            int vis = -1;
            for (int j = 0; j < ansid; ++j)
                if (cnt[v[j].id])
                {
                    vis = v[j].id; // 找到还有空余的字母
                    break;
                }
            s[i] = vis + 'a'; // 进行分配
            --cnt[vis];
        }
        cout << s << '\n';
    }
    cout.flush();
    return 0;
}
```

## 3. 附注

一般来说，构造题可以进行适当枚举，以约束构造的范围。另外，一定注意题目中一些变量的范围，这可以帮助我们选择更好的做法。


---

## 作者：xieziheng (赞：2)

~~我大概是脑子不太好，碰到 cf 的思维题基本都不会。~~

记录一下我调 $2$ 小时代码的过程。

我开始想了个错误的结论：首先发现合法字符串中出现的字母数量一定是 $n$ 的因数，设为 $a$，设初始字符串中有 $m$ 个字母，那么答案字符串中的字母数量应该和 $a$ 的差最小。然而，事实证明，这是错的。比如 $\texttt{ sasaasalssedsalaqalq}$ 长度为 $20$，共 $6$ 个字母，改成 $\texttt{llsqasalssqqsalaqalq}$ ($4$ 个字母) 更好，而不是 $5$ 个。

~~在我惨痛的教训后，~~ 可知需要对 $n$ 的每个因数都判断一下。具体来说，对于 $n$ 的因数 $a$，此时合法字符串中每个字母出现的次数为 $\frac n a$。记第 $i$ 个字母出现次数为 $f_i$，其距离为 $|f_i-\frac n a|$，跟据距离越小越优贪心的选择 $a$ 个字母。统计答案时碰到没选的或要选且选多了的字母就把他改成要选且选少了的字母，最后修改的次数和得到的字符串就是答案。

$Code:$

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
il bool isletter(char c){return c>='a' && c<='z';}
il string reads(){
	string s="";char c=getchar();
	while(!isletter(c)) c=getchar();
	while(isletter(c)) s+=c,c=getchar();
	return s; 
}
il int cmin(int x,int y){return x>y?y:x;}
il int cmax(int x,int y){return x>y?x:y;}
il int ab(int x){return x>=0?x:-x;}
const int N=1e5+5,M=30,inf=1e9;
int T,n,ans,in[N],a[N],vis[N];
//in:the times each letter appear in s,a:the priority for each letter,vis:choose it or not
string str;char s[N];
il bool cmp(int x,int y){return in[x]<in[y];}
int x,y;
il int solve(int num){//num:numbers of different letters
	int siz=n/num,cur=inf,pos=0,sum=0;
	for(int i=0;i<26;++i) in[i]=vis[i]=0,a[i]=i;
	for(int i=1;i<=n;++i) s[i]=str[i-1],++in[s[i]-'a'];
	sort(a,a+26,cmp);
	for(int i=0;i+num-1<26;++i){
		x=y=0;
		for(int j=i;j<=i+num-1;++j) in[a[j]]<=siz?x+=siz-in[a[j]]:y+=in[a[j]]-siz;
		cur=cmin(cur,cmax(x,y));
	}
	for(int i=0;i+num-1<26;++i){
		x=y=0;
		for(int j=i;j<=i+num-1;++j) in[a[j]]<=siz?x+=siz-in[a[j]]:y+=in[a[j]]-siz;
		if(cmax(x,y)==cur) pos=i;
	}
	for(int i=pos;i<=pos+num-1;++i) vis[a[i]]=1;
	for(int i=1;i<=n;++i)
		if(!vis[s[i]-'a'] || (vis[s[i]-'a'] && in[s[i]-'a']>siz))
			for(int j=0;j<26;++j)
				if(vis[j] && in[j]<siz){++in[j],--in[s[i]-'a'],s[i]=char(j+'a'),++sum;break;}
	for(int i=0;i<26;++i) if(vis[i] && in[i]!=siz) return inf;
	return sum;
}
il void putout(int num){//the same as before
	int siz=n/num,cur=inf,pos=0,sum=0;
	for(int i=0;i<26;++i) in[i]=vis[i]=0,a[i]=i;
	for(int i=1;i<=n;++i) s[i]=str[i-1],++in[s[i]-'a'];
	sort(a,a+26,cmp);
	for(int i=0;i+num-1<26;++i){
		x=y=0;
		for(int j=i;j<=i+num-1;++j) in[a[j]]<=siz?x+=siz-in[a[j]]:y+=in[a[j]]-siz;
		cur=cmin(cur,cmax(x,y));
	}
	for(int i=0;i+num-1<26;++i){
		x=y=0;
		for(int j=i;j<=i+num-1;++j) in[a[j]]<=siz?x+=siz-in[a[j]]:y+=in[a[j]]-siz;
		if(cmax(x,y)==cur) pos=i;
	}
	for(int i=pos;i<=pos+num-1;++i) vis[a[i]]=1;
	for(int i=1;i<=n;++i)
		if(!vis[s[i]-'a'] || (vis[s[i]-'a'] && in[s[i]-'a']>siz))
			for(int j=0;j<26;++j)
				if(vis[j] && in[j]<siz){++in[j],--in[s[i]-'a'],s[i]=char(j+'a'),++sum;break;}
	printf("%d\n",sum);
	for(int i=1;i<=n;++i) printf("%c",s[i]);
	printf("\n");
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);str=reads(),ans=inf;
		for(int i=1;i<=n;++i) s[i]=str[i-1];
		for(int i=1;i<=n;++i) if(n%i==0) ans=cmin(ans,solve(i));
		for(int i=1;i<=n;++i) if(n%i==0 && solve(i)==ans){putout(i);break;} 
	}
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF1781C Equal Frequencies
## 题目翻译
给定一个字符串 $s$，定义一个字符串是好的仅当其中每个字符出现次数相同，现在要使字符串变成好的所使用步数最少，求一个最优更改后的字符串。
## 常见套路
由于一共只有 $26$ 个字符，所以我们可以暴力枚举留下几个字符。那么此时必须满足一个性质：留下字符数一定能整除总长度（否则根据抽屉原理一定不合法）。\
那么假设留下的字符数量为 $x$，我们就开始确定构造策略。\
第一步我们可以确定每个字符最终出现次数 $w$（直接 $w=\frac{|s|}{x}$）\
第二步，出现次数最多的 $x$ 个字符一定保留。显然如果这些字符大于 $w$，那么留下它肯定比拿一个少的补齐更优秀；如果它都比 $w$ 小了，那其他的肯定要补的更多。\
那么确定了最终要哪些字符和每个字符出现次数，直接模拟补的过程即可（多的改成少的）。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,ansid;
int vis[26],used[26];
struct node{
    char ch;
    int times;
    bool operator <(node c1)const{
        if(times!=c1.times)return times<c1.times;
        return ch<c1.ch;
    }
}num[26];
string s;
int getans(int x){
    int res=0;
    int numone=n/x;
    for(int i=25;i>25-x;--i){
        if(num[i].times<numone){
            res+=numone-num[i].times;
        }else{
            res+=num[i].times-numone;
        }
    }
    for(int i=25-x;i>=0;--i){
        res+=num[i].times;
    }
    return res/2;
}
void make(int x){
    set<char>need;
    int numone=n/x;
    memset(vis,0,sizeof(vis));
    memset(used,0,sizeof(used));
    for(int i=25;i>25-x;--i){
        used[num[i].ch-'a']=1;
    }
    for(int i=25;i>=0;--i){
        if(num[i].times>numone){
            vis[num[i].ch-'a']=num[i].times-numone;
        }
        if(num[i].times<numone){
            if(used[num[i].ch-'a']){
                vis[num[i].ch-'a']=num[i].times-numone;
                need.insert(num[i].ch);
            }
            else{
                vis[num[i].ch-'a']=num[i].times;
            }
        }
    }
    for(char c:s){
        if(vis[c-'a']<=0){
            cout<<c;
        }
        else if(vis[c-'a']>0){
            char ch=*need.begin();
            cout<<ch;
            vis[ch-'a']++;
            if(vis[ch-'a']==0){
                need.erase(ch);
            }
            vis[c-'a']--;
        }
    }
    cout<<'\n';
}
void solve(){
    cin>>n>>s;
    for(int i=0;i<26;++i){
        num[i].ch=char('a'+i);
        num[i].times=0;
    }
    for(char c:s){
        num[c-'a'].times++;
    }
    sort(num,num+26);
    ans=ansid=114514;
    for(int i=1;i<=26;++i){
        if(n%i==0){
            int nowans=getans(i);
            if(nowans<ans){
                ansid=i;
                ans=nowans;
            }
        }
    }
    cout<<ans<<"\n";
    make(ansid);
    return;
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

