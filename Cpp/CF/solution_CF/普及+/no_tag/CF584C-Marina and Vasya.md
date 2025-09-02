# Marina and Vasya

## 题目描述

Marina loves strings of the same length and Vasya loves when there is a third string, different from them in exactly $ t $ characters. Help Vasya find at least one such string.

More formally, you are given two strings $ s_{1} $ , $ s_{2} $ of length $ n $ and number $ t $ . Let's denote as $ f(a,b) $ the number of characters in which strings $ a $ and $ b $ are different. Then your task will be to find any string $ s_{3} $ of length $ n $ , such that $ f(s_{1},s_{3})=f(s_{2},s_{3})=t $ . If there is no such string, print $ -1 $ .

## 样例 #1

### 输入

```
3 2
abc
xyc
```

### 输出

```
ayd```

## 样例 #2

### 输入

```
1 0
c
b
```

### 输出

```
-1
```

# 题解

## 作者：xzy090626 (赞：0)

很有意思的构造题啊。容易想麻烦。

首先经典技巧是先把答案串设成 $a$ 再进行修改，这样保证这个串和 $a$ 的不同位置一定在修改中是减少的。

然后对于 $a_i\neq b_i$ 的位置，我们先把这个位置改成某个字符使得它既不是 $a_i$ 也不是 $b_i$。这样会保证答案串当前与 $a$ 和 $b$ 不同的位置相等。设当前不同的位置个数为 $d$。

---

然后开始操作。先计算当前不同的位置，遍历整个字符串，
- 如果 $d>t$，我们需要增加相同的位置，于是对于 $a_i\neq b_i$ 的位置，我们需要把答案串的对应位置改成 $a_i$ 或者 $b_i$。那么到底改成谁呢？我们考虑到原本不同的位置已经相等了，于是轮流修改即可。
- 如果 $d<t$，我们需要增加不同的位置，于是对于 $a_i=b_i$，我们改成不同的字符即可。

那么如何证明这个做法是最优的呢？显然我们预处理的过程中已经对于 $a_i=b_i$ 的情况最大化了相同位置的个数，于是再想减少这个个数就一定只能对于 $a_i\neq b_i$ 的地方进行修改了。也就是说我们修改的操作策略总是唯一的。

```cpp
int n,t,d;
string a,b,s;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>t>>a>>b;
	s = a;
	for(int i=0;i<n;++i){
		if(a[i]!=b[i]){
			d++;
			for(char c='a';c<='z';++c){
				if(c!=a[i] && c!=b[i]){
					s[i] = c;
					break;
				}
			}
		}
	}
	d = (d-t)*2;
	int ff = 1;
	for(int i=0;i<n;++i){
		if(d<0 && a[i]==b[i]){
			d += 2;
			for(char c='a';c<='z';++c){
				if(c!=a[i] && c!=b[i]){
					s[i] = c;
					break;
				}
			}			
		}
		else if(d>0 && a[i]!=b[i]){
			d--;
			s[i] = ff?b[i]:a[i];
			ff ^= 1;
		}
	}
	if(!d) cout<<s;
	else cout<<-1;
	return 0;
}
```

---
不过，还有第二种构造方案，思路其实与上面类似：我们在预处理时让答案串每个位置都与两个串不同。这个思路更简洁也更直接。

于是在操作的时候只需要减少不同的位置个数即可。但是这个时候我们就需要考虑修改顺序的问题了：因为我们到底是对于 $a_i\neq b_i$ 的情况修改为其中一个，还是对 $a_i=b_i$ 的情况修改为相同的？我们优先做第二种，然后再做第一种即可。原因是第二种能减少总体的个数更多，而且不改变 $d$ 的奇偶性。

```cpp
int n,t,d;
string a,b,s;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>t>>a>>b;
	s = a;
	for(int i=0;i<n;++i){
		for(char c='a';c<='z';++c){
			if(c!=a[i] && c!=b[i]){
				s[i] = c;
				break;
			}
		}
		d++;
	}
	d = (d-t)*2;
	int ff = 1;
	for(int _=0;_<=1;++_){
		for(int i=0;i<n;++i){
			if(d>=1 && a[i]!=b[i] && _==1){
				d--;
				s[i] = ff?b[i]:a[i];
				ff ^= 1;
			}
			else if(d>=2 && a[i]==b[i] && _==0){
				d-=2;
				s[i] = a[i];
			}
		}
	}
	if(!d) cout<<s;
	else cout<<-1;
	return 0;
}
```

---

题解文字内容可能有些难懂，可以通过代码辅助理解。

---

## 作者：luo_shen (赞：0)

随机跳题跳到的，感觉很像[这道题](https://www.luogu.com.cn/problem/AT_arc151_a)的加强版。
## 题意描述
令 $f(a,b)$ 表示两个字符串中有多少个位置字符不同，给定字符串 $s_1,s_2$ 和一个正整数 $t$，要求构造一个字符串 $s_3$，使得 $f(s_1,s_3)=f(s_2,s_3)=t$。
## 题目分析
首先考虑无解的情况，显然可以发现：若存在一个 $i$，使得 $s_{1,i}\not= s_{2,i}$，则 $f(s_1,s_3),f(s_2,s_3)$ 中至少有一个要上升 $1$。若存在 $tot$ 个这样的 $i$，考虑将上升的部分平均一下，则要求 $\lceil\frac{tot}{2}\rceil\le t$，才能构造出一个符合条件的 $s_3$，即当 $t\times 2 \ge tot$ 时无解。

对于有解的情况，先让其满足最小条件，将 $tot$ 个位置平均分配一下，使其中一半的位置符合 $s_{3,i}=s_{1,i}$，另一半的位置符合 $s_{2,i}=s_{1,i}$，剩下的 $len-tot$ 个位置三个字符串的字母均相等。

接下来就是进行调整。首先调整的是两个串不同的 $tot$ 个位置，将 $s_{3,i}$ 改为与 $s_{1,i},s_{2,i}$ 均不同的字符，若 $tot$ 个位置全部改完后，$f(s1,s3)\not= t$，修改剩下的 $n-tot$ 个字符，直到 $f(s1,s3)=t$ 即可。

## Code
```cpp
signed main(){
    read(len),read(sum);
    scanf("%s",s+1);
    scanf("%s",t+1);
    int tot=0;
    for(int i=1;i<=len;i++){//标记两个串中字符相同和不同的位置
        if(s[i]==t[i]){
            b[i]=1;
        }
        else{
            tot++;
            b[i]=0;
        }
    }
    if(sum*2<tot){//判断无解
        write_endl(-1);
        return 0;
    }
    int sum1=sum,sum2=sum;//sum1表示t-f(s1,s3)的大小，sum2表示t-f(s2,s3)的大小
    for(int i=1;i<=len;i++){
        if(b[i]==1){//相同的先填上
            ans[i]=s[i];
        }
        else{//平均分配两个串中字符不同的位置
            if(sum1>sum2){
                ans[i]=t[i];
                sum1--;
            }
            else{
                sum2--;
                ans[i]=s[i];
            }
        }
    }
    for(int i=1;i<=len;i++){//修改最初的决策，进行调整
        if(sum1&&s[i]==ans[i]&&t[i]!=ans[i]){//若f(s1,s3)<t且对增加f(s1,s3)有影响的位置才调整
            sum1--;
            for(int j=0;j<26;j++){//随意找一个与两个串中的字符均不同的字符即可，下同
                if(j+'a'!=s[i]&&j+'a'!=t[i]){
                    ans[i]=j+'a';
                    break;
                }
            }
        }
        else if(sum2&&t[i]==ans[i]&&s[i]!=ans[i]){//若f(s2,s3)<t且对增加f(s2,s3)有影响的位置才调整
            sum2--;
            for(int j=0;j<26;j++){
                if(j+'a'!=s[i]&&j+'a'!=t[i]){
                    ans[i]=j+'a';
                    break;
                }
            }
        }
    }
    if(sum1){//若f(s1,s3)仍小于t
        for(int i=1;i<=len;i++){
            if(sum1&&ans[i]==s[i]&&ans[i]==t[i]){//修改两串中字符相同的位置
                for(int j=0;j<26;j++){
                    if(j+'a'!=s[i]){
                        ans[i]=j+'a';
                        sum1--;
                        break;
                    }
                }
            }
        }
    }
    for(int i=1;i<=len;i++){
        putchar(ans[i]);
    }
    return 0;
}
```

---

