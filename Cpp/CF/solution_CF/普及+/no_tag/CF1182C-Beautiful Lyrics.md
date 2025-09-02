# Beautiful Lyrics

## 题目描述

You are given $ n $ words, each of which consists of lowercase alphabet letters. Each word contains at least one vowel. You are going to choose some of the given words and make as many beautiful lyrics as possible.

Each lyric consists of two lines. Each line consists of two words separated by whitespace.

A lyric is beautiful if and only if it satisfies all conditions below.

- The number of vowels in the first word of the first line is the same as the number of vowels in the first word of the second line.
- The number of vowels in the second word of the first line is the same as the number of vowels in the second word of the second line.
- The last vowel of the first line is the same as the last vowel of the second line. Note that there may be consonants after the vowel.

Also, letters "a", "e", "o", "i", and "u" are vowels. Note that "y" is never vowel.

For example of a beautiful lyric,

 "hello hellooowww" "whatsup yowowowow"

 is a beautiful lyric because there are two vowels each in "hello" and "whatsup", four vowels each in "hellooowww" and "yowowowow" (keep in mind that "y" is not a vowel), and the last vowel of each line is "o".For example of a not beautiful lyric,

 "hey man""iam mcdic"

 is not a beautiful lyric because "hey" and "iam" don't have same number of vowels and the last vowels of two lines are different ("a" in the first and "i" in the second).How many beautiful lyrics can you write from given words? Note that you cannot use a word more times than it is given to you. For example, if a word is given three times, you can use it at most three times.

## 说明/提示

In the first example, those beautiful lyrics are one of the possible answers. Let's look at the first lyric on the sample output of the first example. "about proud hooray round" forms a beautiful lyric because "about" and "hooray" have same number of vowels, "proud" and "round" have same number of vowels, and both lines have same last vowel. On the other hand, you cannot form any beautiful lyric with the word "codeforces".

In the second example, you cannot form any beautiful lyric from given words.

In the third example, you can use the word "same" up to three times.

## 样例 #1

### 输入

```
14
wow
this
is
the
first
mcdics
codeforces
round
hooray
i
am
proud
about
that
```

### 输出

```
3
about proud
hooray round
wow first
this is
i that
mcdics am
```

## 样例 #2

### 输入

```
7
arsijo
suggested
the
idea
for
this
problem
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
same
same
same
differ
```

### 输出

```
1
same differ
same same
```

# 题解

## 作者：redegg (赞：1)

史前暴力写法，贪心把符合要求的两个两个成对全部丢到队列里面，分两个队列，一个是开头队列只满足元音字母数相等，第二个是末尾队列满足元音同时满足最后一个元音相同。

然后就是成对取出配对，当然当开头队列的数量不够时也可以用队尾队列来凑。整体思路就是暴力啊，脑子不够手指来凑。


```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

string in[100005];

struct ha
{
    int last,len,id;
}a[1000005];

bool cmp(const ha &aa,const ha &bb)
{
    if(aa.len!=bb.len)
        return aa.len<bb.len;
    return aa.last<bb.last;
}

queue<int> lq;
queue<int> nq;
int m;
queue<int> an;

queue<int> lins;
queue<int> linsl;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>in[i];
        a[i].id=i;
        int l=in[i].size();
        a[i].len=0;
        for(int j=0;j<l;j++)
        {
            if(in[i][j]=='a'||in[i][j]=='e'||in[i][j]=='i'||in[i][j]=='o'||in[i][j]=='u')
            {
                a[i].len++;
                a[i].last=in[i][j]-'a';
            }
        }
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        if(a[i].len==a[i+1].len&&a[i].last==a[i+1].last)
        {
            lq.push(a[i].id);
            lq.push(a[i+1].id);
            i++;
            continue;
        }
        lins.push(a[i].id);
        linsl.push(a[i].len);
    }
    while(!lins.empty())
    {
        int nq1=lins.front();
        lins.pop();
        int L1=linsl.front();
        linsl.pop();
        if(lins.empty())break;
        int nq2=lins.front();
        int L2=linsl.front();
        if(L1==L2)
        {
            lins.pop();
            linsl.pop();
            nq.push(nq1);
            nq.push(nq2);
        }
    }
    int ans1=0,ans2=0,ans3=0,ans4=0;
    while(!nq.empty())
    {
        ans1=nq.front(),ans2,ans3,ans4;
        nq.pop();
        if(nq.empty())break;
        ans2=nq.front();
        nq.pop();
        if(lq.empty())break;
        if(!lq.empty())
        {
            ans3=lq.front();
            lq.pop();
            ans4=lq.front();
            lq.pop();
        }
        m++;
        an.push(ans1);
        an.push(ans3);
        an.push(ans2);
        an.push(ans4);
        ans1=0,ans2=0,ans3=0,ans4=0;
    }
    while(!lq.empty())
    {
        if(ans1>0)
        {
            ans2=lq.front();
            lq.pop();
            if(lq.empty())break;
            ans3=lq.front();
            lq.pop();
            if(lq.empty())break;
            ans4=lq.front();
            lq.pop();
            m++;
            an.push(ans1);
            an.push(ans3);
            an.push(ans2);
            an.push(ans4);
            ans1=0,ans2=0,ans3=0,ans4=0;
        }
        else
        {
            ans1=lq.front();
            lq.pop();
            if(lq.empty())break;
            ans2=lq.front();
            lq.pop();
            if(lq.empty())break;
            ans3=lq.front();
            lq.pop();
            if(lq.empty())break;
            ans4=lq.front();
            lq.pop();
            m++;
            an.push(ans1);
            an.push(ans3);
            an.push(ans2);
            an.push(ans4);
            ans1=0,ans2=0,ans3=0,ans4=0;
        }
    }
    printf("%d\n",m);
    while(!an.empty())
    {
        ans1=an.front();
        an.pop();
        ans3=an.front();
        an.pop();
        ans2=an.front();
        an.pop();
        ans4=an.front();
        an.pop();
        cout<<in[ans1]<<" "<<in[ans3]<<endl;
        cout<<in[ans2]<<" "<<in[ans4]<<endl;
    }
    return 0;
}
```


---

## 作者：fly20040720 (赞：0)

这题没有什么思维难度，就是讲所有的词以元音字母个数为第一关键字，最后一个元音字母为第二关键字排序。期中第二关键字是为了保证如果在所有元音字母个数相同的单词中，最后一个字母相同的（即能作为第二个单词的）位置连续。

排好序之后，对于所有可行的组合进行统计。这些组合分成两类：只能放在第一个的和两个位置都可以的。

最后输出即可，具体解释见代码。
```
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<int> VI;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define EACH(i,c) for(__typeof((c).begin()) i=(c).begin(),i##_end=(c).end();i!=i##_end;++i)

int N;
char buf[1000011];

struct Data
{
	int cnt;
	char last;
	string s;

	bool operator<(const Data &o) const
	{
		return cnt != o.cnt ? cnt < o.cnt : last < o.last;
	}
};//用于记录每一个字符串的元音字母个数，最后一个元音字母以及本身（输出要用）

int main()
{
	scanf("%d", &N);
	vector<Data> v, w, x, y;
	REP (i, N)
	{
		scanf("%s", buf);
		int len = strlen(buf);
		int cnt = 0;
		char last = 0;
		REP (j, len)
		{
			switch (buf[j])
			{
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u':
					cnt++;
					last = buf[j];
					break;
                //case的特性：不加break就会执行下面所有的语句
			}
		}

		v.push_back((Data)
		{
			cnt, last, buf
		});
	}

	sort(v.begin(), v.end());
	REP (i, v.size())
	{
		if (i + 1 < (int)v.size() && v[i].cnt == v[i+1].cnt && v[i].last == v[i+1].last)
		{
			w.push_back(v[i]);
			w.push_back(v[i+1]);
			i++;
		}
		else
		{
			x.push_back(v[i]);
		}
	}//先处理能作为第二个的，因为所有能做第二个的pair都能做第一个
	REP (i, x.size())
	{
		if (i + 1 < (int)x.size() && x[i].cnt == x[i+1].cnt)
		{
			y.push_back(x[i]);
			y.push_back(x[i+1]);
			i++;
		}
	}//第二个挑剩下的中找符合条件的

	vector<string> ans;
	while (1)
	{
		if (!w.empty() && !y.empty())
		{
			REP (t, 2)
			{
				ans.push_back(y.back().s);
				y.pop_back();
				ans.push_back(w.back().s);
				w.pop_back();
			}
		}
		else if (w.size() >= 4)
		{
			string tmp1 = w.back().s;
			w.pop_back();
			string tmp2 = w.back().s;
			w.pop_back();
			ans.push_back(w.back().s);
			w.pop_back();
			ans.push_back(tmp1);
			ans.push_back(w.back().s);
			w.pop_back();
			ans.push_back(tmp2);
		}
		else
		{
			break;
		}
	}//生成答案，先把其中一个用完，如果第二个里面还有剩余，就自己搭配自己

	printf("%d\n", (int)ans.size() / 4);
	REP (i, ans.size()/2)
	{
		printf("%s %s\n", ans[i*2].c_str(), ans[i*2+1].c_str());
	}
	return 0;
}

---

