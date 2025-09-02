# [NEERC 2016] List of Primes

## 题目描述

Lidia 喜欢质数集合。当她感到无聊时，她就开始把它们写在极长的质数集合笔记本上。

每个集合的元素按升序排列。每个质数集合最终都会出现在她的笔记本上。和较小的集合总是出现在和较大的集合之前。和相同的集合按字典序升序排列：它们首先比较第一个元素，如果第一个元素相同，则比较第二个元素，依此类推。

以防有人决定解析她的笔记本，她将她的集合写成机器可读的 JSON 格式。当然，她在每个逗号后面加了一个空格。以下是她笔记本的开头：

$[2], [3], [2 , 3], [5], [2 , 5], [7], [3 , 5], [2 , 7], [2 , 3 , 5], [3 , 7], [11], [2 , 3 , 7], [5 , 7], [2 , 11], [13], [2 , 5 , 7],$

Lidia 想要仔细检查她的工作，所以她请求你：给定两个整数 $a$ 和 $b$，输出她的笔记本中从位置 $a$ 到位置 $b$（包括，位置从 $1$ 开始计数）的子字符串。

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1 35
```

### 输出

```
[2], [3], [2, 3], [5], [2, 5], [7],
```

## 样例 #2

### 输入

```
36 41
```

### 输出

```
 [3, 5
```

# 题解

## 作者：Alex_Wei (赞：10)

> [题目传送门](https://www.luogu.com.cn/problem/P6973)。
>
> 题意简述：将质数集合的所有子集按照子集和为第一关键字，字典序为第二关键字从小到大排序，求最终形成的字符串的第 $l\sim r$ 个字符。
>
> [在 cnblogs 内查看](https://www.cnblogs.com/alex-wei/p/P6973_NEERC2016L.html)。

---

又是一道妙妙题。

首先考虑当 $r\leq 10^5$ 时直接搜索，首先**枚举子集和 $i$**，状态是 $sum,len,lim$ 表示**剩余**子集和为 $sum$，大小为 $len$，接下来只能使用第 $lim$ 个及以后的质数。边界是 $sum=0$，表示找到一个符合题意的子集。

直接暴力跑大概可以过 $r\leq 10^5$，不过有一个显然的剪枝：预处理 $f_{i,j}$ 表示只用第 $j$ 个及以后的质数能否拼出 $sum=i$，爆搜下一个分支时可以快速判断是否合法，从而避免进入不合法的分支。这样一来复杂度就变成了线性 $\mathcal{O}(r)$。

---

$r\leq 10^{18}$ 时，我们继续选择搜索。观察到 $r-l\leq 10^5$，所以如果已经遍历过的子集长度总和 与 接下来的分支所形成的的子集长度总和 之和仍小于 $l$，那么根本没有必要遍历该分支。对此，我们预处理 $g_{i,j}$ 表示只用第 $j$ 个及以后的质数拼出的所有子集的长度之和（不考虑两边的中括号和逗号 $\texttt{[],}$），同时更改 $f_{i,j}$ 的定义：只用第 $j$ 个及以后的质数拼出来的子集个数。这是一个显然的 DP：**从大到小枚举** $j$，那么有 $f_{i,j}\gets f_{i,j+1}+f_{i+pr_j,j+1}$，$g_{i,j}\gets g_{i,j+1}+(g_{i+pr_j,j+1}+(bit(pr_j)+2)\times f_{i+pr_j,j+1})$，其中 $pr_j$ 表示第 $j$ 个质数，$bit(x)$ 表示 $x$ 在十进制下的位数，有 $+2$ 是因为两个数之间有长度为 $2$ 的逗号 + 空格。同时你可以根据 DP 很容易地求出来 $i$ 的上界大约在 $2.1\times 10^3$ 左右，那么 $j$ 只需要开到 $350$ 即可。

爆搜时，我们记录一个全局变量 $acc(umulation)$ 表示已经遍历过的子集长度，此外还要在状态中加入 $slen$ 表示当前分支已经选择的质数的长度之和，即 $\sum_{p\in \mathrm{chosen}}bit(p)$（原因接下来会讲）。

---

首先判断搜索边界：$sum$ 是否 $=0$。是 $0$ 就表示遍历到了一个子集，将该子集计入答案并返回，否则根据已有的信息算出**该分支接下来所能产生的所有子集的长度之和**，与 $acc$ 求和后看是否小于 $l$，若小于，则直接更新 $acc$ 并返回即可。否则继续搜索即可。

接着考虑到了搜索边界该干什么：如果遍历到了一个子集，那么一个字符一个字符地考虑：插入一个字符时，首先将 $acc$ 自增 $1$，如果 $acc>r$ 那么退出程序；否则，如果 $acc\geq l$ 那么输出该字符；否则啥也不干。

怎么根据已有的信息算出该分支的子集长度总和呢？因为能产生 $f_{sum,lim}$ 个子集，因此 $acc$ 长度加上：

- $4f_{sum,lim}$ 表示边界的四个字符：$\texttt{'[', ']', ',', ' '}$。
- $(len-1)\times 2f_{sum,lim}$ 表示已经选择的 $len$ 个数所产生的 $len-1$ 个长度为 $2$ 的间隔 $\texttt{‘,’, ‘ ’}$（代码中 $len$ 的初始值为 $1$，所以是 $2len$）。
- $g_{sum,lim}$（这个就不用解释了吧 = . =）。
- $slen\times f_{sum,lim}$ 表示已经选择的质数长度在所有 $f_{sum,lim}$ 个子集中所贡献的长度之和，这也是我们要记录 $slen$ 的原因。

时间复杂度 $\mathcal{O}(r-l)$，也可以说是 $\mathcal{O}(n\pi(n))$，其中 $n\approx 2100$。

此外，今天是 2021 年的七夕节（8.14），祝大家七夕快乐，早日脱单（大雾）！

```cpp
const int N=2100+5;
const int P=350;

int cnt,vis[N],pr[N],bt[N];
ll f[N][P],g[N][P];
void init(){
	for(int i=2;i<N;i++){
		if(vis[i])continue;
		pr[++cnt]=i,f[i][cnt]=1,g[i][cnt]=bt[i]=log10(i)+1;
		for(int j=i+i;j<N;j+=i)vis[j]=1;
	}
	for(int i=cnt;i;i--){
		int len=bt[pr[i]]+2;
		for(int j=pr[i];j<N;j++)
			f[j][i]+=f[j-pr[i]][i+1]+f[j][i+1],
			g[j][i]+=g[j-pr[i]][i+1]+g[j][i+1]+f[j-pr[i]][i+1]*len;
	}
}

ll l,r,acc,p[N];
string to_str(int x){
	string s;
	while(x)s+=x%10+'0',x/=10;
	reverse(s.begin(),s.end());
	return s;
}
void add(char s){
	if(++acc>r)exit(0);
	if(acc>=l)cout<<s;
}

void dfs(int sum,int len,int lim,ll slen){
	if(!sum){
		add('[');
		for(int i=1;i<=len;i++){
			string s=to_str(p[i]);
			for(int j=0;j<s.size();j++)add(s[j]);
			if(i<len)add(','),add(' ');
		} add(']'),add(','),add(' ');
		return;
	}
	ll nw=acc+(len*2+4+slen)*f[sum][lim]+g[sum][lim];
	if(nw<l)return acc=nw,void();
	len++;
	for(int j=lim;j<=cnt;j++){
		int res=sum-pr[j]; p[len]=pr[j];
		if(res<0)break;
		if(res==0||f[res][j])dfs(res,len,j+1,slen+bt[pr[j]]);
	}
}

int main(){
	init(),cin>>l>>r;
	for(int i=2;i<N;i++)dfs(i,0,1,0);
	return 0;
}
```



---

