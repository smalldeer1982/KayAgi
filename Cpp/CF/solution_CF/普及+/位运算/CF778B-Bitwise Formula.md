# Bitwise Formula

## 题目描述

Bob 最近对计算机中的位运算（AND、OR 和 XOR）产生了兴趣。他研究了这些运算的特性，并发明了一种新型游戏。

首先，Bob 选择一个整数 $m$，代表游戏的位数限制。这意味着游戏中所有参与的数字都由 $m$ 位构成。接着，他让 Peter 选择一个 $m$ 位的数。然后，Bob 根据这个数计算出 $n$ 个变量的值。每个变量的值要么是一个固定的 $m$ 位常量，要么是通过位运算得到的结果。运算的操作数可以是之前定义的变量，或者是 Peter 选择的那个数。最后，Peter 的得分为所有变量值的总和。

现在，Bob 想知道：Peter 应该选择什么数以得到可能的最低总得分？又该选择什么数以得到可能的最高总得分？如果有多种选择，应该输出 Peter 可以选择的最小那个数。

## 说明/提示

在第一个示例中，如果 Peter 选择数字 $011_2$，则 $a = 101_2$, $b = 011_2$, $c = 000_2$，变量值的总和为 $8$。如果他选择数字 $100_2$，则 $a = 101_2$, $b = 011_2$, $c = 111_2$，总和为 $15$。

对于第二个测试例，变量 $a$，$bb$，$cx$，$d$ 和 $e$ 的最小及最大总和均为 $2$，而这个总和并不受 Peter 选择的数字影响，因此 Peter 可以选择的最小目标数为 $0$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 3
a := 101
b := 011
c := ? XOR b
```

### 输出

```
011
100
```

## 样例 #2

### 输入

```
5 1
a := 1
bb := 0
cx := ? OR a
d := ? XOR ?
e := d AND bb
```

### 输出

```
0
0
```

# 题解

## 作者：QWQ_123 (赞：0)

显然的，每一位独立。

所以对于未知数每一位，我们分别考虑这一位填 $0$ 还是 $1$。

若填 $0,1$ 带来的贡献相同，那么最小值和最大值的当前位都填 $0$，否则最大值就填贡献大的那个数，最小值就填贡献小的那个数。

---

## 作者：UnyieldingTrilobite (赞：0)

首先选定的这个数显然每一位是独立的（因为表达式只有位运算），所以完全可以按位贪心然后模拟。

从高到低枚举每一位如果是 0 那么这一位会对总和产生多少贡献，反之会产生多少贡献，然后就可以判断如果要总和最大应该填 0 还是 1，如果最小要填 0 还是 1 了。

有个小小细节，如果贡献一样，那么根据题目要求的最小值，应该总和最大和总和最小的字符串这一位都填 0。

然后根据问号推算全局这部分其实挺好写的，反正我是贪图 `split` 然后上了个 Python3……Py3 坑点我也稍微讲一下吧：常数过大……

具体卡法大概就是读入字符串的时候就直接存下标，而不是存字符串然后到散列表里查，然后开 PyPy3 大概信仰一发就能过了。

代码：

```python
n,m=map(int,input().split())
ansmin,ansmax=[],[]
mp={'?':0}# 变量名到下标的映射
expr=[]# 输入的表达式
def trans(s):
	return '0'*(m-len(s))+s if s.isdigit() else mp[s]# 多功能函数，参数为字符串，如果是数字就补全到 m 位否则转为下标
for i in range(n):
	x=input().split(' := ')
	mp[x[0]]=i+1
	if ' 'in x[1]:# :=右边有运算符
		w=x[1].split(' ')
		w[0]=trans(w[0])
		w[2]=trans(w[2])
		expr.append((i+1,w))
	else:
		expr.append((i+1,[trans(x[1])]))
val=[None]*(n+1)# 用来存变量的值
def op(l,r,s):
	if s=='XOR':
		return l!=r
	elif s=='OR':
		return l|r
	else:
		return l&r
for t in range(m):
	def getvalof(s):# 获取一个数/变量的值
		if type(s)==str:
			return True if s[t]=='1' else False
		else:
			return val[s]
	def getval(s):# 获取一个表达式（列表）的值
		if len(s)==1:
			return getvalof(s[0])
		else:
			a,b=getvalof(s[0]),getvalof(s[2])
			return op(a,b,s[1])
	val[0]=True# 枚举当前位是 1
	cnt1=0
	for name,sym in expr:
		b=getval(sym)
		val[name]=b
		cnt1+=b
	val[0]=False# 枚举当前位是 0
	cnt2=0
	for name,sym in expr:
		b=getval(sym)
		val[name]=b
		cnt2+=b
	if cnt1<cnt2:
		ansmin.append('0')
		ansmax.append('1')
	elif cnt1>cnt2:
		ansmin.append('1')
		ansmax.append('0')	
	else:
		ansmin.append('0')
		ansmax.append('0')
print(''.join(ansmax))
print(''.join(ansmin))
	
```

---

## 作者：xukuan (赞：0)

一开始把这题当成字符串模拟了，后来才发现是数学。

我们可以发现：所有数的位数相同，所以高位的影响大于地位

我们优先考虑高位。

对于每一位，每一位只有0/1两种情况，穷举即可。

程序片段：
```cpp
inline ll work(ll x,ll p){
    digit[0].number=p; ll ans=0;
    for(ll i=1; i<=n; i++){
        if(digit[i].opt==0) digit[i].number=digit[i].s[x]-48;
        else{
            ll x=digit[digit[i].x].number,y=digit[digit[i].y].number;
            if(digit[i].opt==1) digit[i].number=x&y;
            else if(digit[i].opt==2) digit[i].number=x|y;
            else if(digit[i].opt==3) digit[i].number=x^y;
        }
        ans+=digit[i].number;
    }
    return ans;
}

int main(){
    cin>>n>>m;
    for(ll i=1; i<=n; i++){
        string s; cin>>s; mp[s]=i; cin>>s>>s;
        if(isdigit(s[0])){digit[i].opt=0;digit[i].s=s;}
        else{
            digit[i].x=mp[s]; cin>>s;
            if(s[0]=='A') digit[i].opt=1;
            else if(s[0]=='O') digit[i].opt=2;
            else if(s[0]=='X') digit[i].opt=3;
            cin>>s; digit[i].y=mp[s];
        }
    }
    string ans1="",ans2="";
    for(ll i=0; i<m; i++){
        ll sum1=work(i,0),sum2=work(i,1);
        if(sum1<=sum2) ans1+='0'; else ans1+='1';
        if(sum1>=sum2) ans2+='0'; else ans2+='1';
    }
    cout<<ans1<<endl<<ans2<<endl;
    return 0;
}
```

---

