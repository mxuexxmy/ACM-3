#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
using namespace std;
typedef long long LL;

struct T {
    int step;
    int num;
    T() {}
    T(int step, int num):step(step),num(num) {}
};

map<string,T>mhead;
map<string, T>::iterator ithead;

queue<string>qhead;
map<string,string>prehead,pretail;
string shead, stail;
int str[2][10];
int n;
int ans;
bool ansFind;

int getNum() {
    int ans = 0;
    int i,j,top,bottom;
    for(i=1; i<=n; i++) {
        for(j=i+1; j<=n; j++) {
            for(top=0; top<2; top++) {
                for(bottom=0; bottom<2; bottom++) {
                    if(str[top][i] > str[bottom][j]) {
                        ans++;
                    }
                }
            }
        }
    }
    return ans;
}

void init() {
    mhead.clear();
    prehead.clear();
    while(!qhead.empty())qhead.pop();
    shead = "";
    for(int i=1; i<=n; i++) {
        for(int j=0; j<2; j++) {
            shead += (str[j][i] + '0');
        }
    }
    mhead[shead] = T(0, getNum());
    qhead.push(shead);
    prehead[shead] = "begin";

    stail = "";
    for(int i=1; i<=n; i++) {
        for(int j=0; j<2; j++) {
            stail += (i+'0');
        }
    }

    ans  = 0;
    if(stail == shead) {
        ansFind = true;
    } else {
        ansFind = false;
    }
}

void toArray(string& s) {
    for(int i=1,j=0; i<=n; i++) {
        for(int k=0; k<2; k++) {
            str[k][i] = s[j++];
        }

    }
}

void toString(string& s) {
    s = "";
    for(int i=1; i<=n; i++) {
        if(str[0][i] > str[1][i]) {
            s += str[1][i];
            s += str[0][i];
        } else {
            s += str[0][i];
            s += str[1][i];
        }
    }
}

int getTwoNum(int i, int j) {
    int ans = 0;
    for(int top=0; top<2; top++) {
        for(int bottom=0; bottom<2; bottom++) {
            if(str[top][i] > str[bottom][j]) {
                ans++;
            }
        }
    }
    return ans;
}

void outputhead(int step, string&s){
	map<string, string>::iterator  it = prehead.find(s);
	if(it == prehead.end()){
		printf("%d:%s\n",step, s.c_str());
	}else{
		outputhead(step-1, it->second);
		printf("%d:%s -> %d\n",step, s.c_str(), mhead[s].num);
	}
}
void outputtail(int step, string&s){
	printf("%d:%s -> 0\n",step, s.c_str());
}

void bfshead() {
    string s = qhead.front();
    qhead.pop();
    shead = s;
    T t = mhead[s];
    int step = t.step;
    int oldnum;
    int newnum ;
    toArray(s);
    int i,j,k;
    for(i=1; i<n; i++) {
    	oldnum = getTwoNum(i,i+1);
        for(j=0; j<2; j++) {
            if(j == 1 && str[1][i] == str[0][i])continue;

            for(k=0; k<2; k++) {
                if(k == 1 && str[1][i+1] == str[0][i+1])continue;

                if(str[j][i] <= str[k][i+1])continue;
                if(str[j][i] <= i + '0' && str[k][i+1] >= i+'1')continue;

                //if(str[j][i] < i - 1 + '0')continue;
                //if(str[k][i+1] > i + 2+ '0')continue;


                swap(str[j][i],str[k][i+1]);

                toString(s);
                ithead = mhead.find(s);

                if(ithead == mhead.end()) {
                    if(s == stail) {
                        ansFind = true;
                        ans = step + 1;
                        outputhead(step, shead);
                        outputtail(step+1, s);
                    } else {
						newnum = getTwoNum(i,i+1);
                        mhead[s] = T(step + 1, t.num - oldnum + newnum);
                        qhead.push(s);
                        prehead[s] = shead;
                    }
                }
                if(ansFind) {
                    return ;
                }
                swap(str[j][i],str[k][i+1]);
            }
        }
    }
}


void bfs() {

    while(!ansFind) {
        //printf("head : %d\n",qhead.size());
        bfshead();
    }

}

int main(int argc, char* argv[]) {
    while(~scanf("%d",&n)) {
        for(int i=1; i<=n; i++) {
            scanf("%d%d",&str[0][i],&str[1][i]);
            if(str[0][i]>str[1][i])swap(str[0][i],str[1][i]);
        }
        init();
        if(!ansFind) {
            bfs();
        }
        printf("%d\n",ans);
        break;
    }

    return 0;
}

/*
8
8 8
7 7
6 6
5 5
4 4
3 3
2 2
1 1

7
7 7
6 6
5 5
4 4
3 3
2 2
1 1

6
6 6
5 5
4 4
3 3
2 2
1 1

5
5 5
4 4
3 3
2 2
1 1

4
4 4
3 3
2 2
1 1

5
1 5
3 4
2 5
2 3
1 4

8
8 3
4 2
6 4
3 5
5 8
7 1
2 6
1 7


0:1534252314
1:1523452314
2:1523243514
3:1523241345
4:1523123445
5:1512233445
6:1125233445
7:1122353445
8:1122334545
9:1122334455

0:1534252314
1:1524352314
2:1245352314
3:1245233514
4:1245231345
5:1224351345
6:1224133545
7:1224133455
8:1212343455
9:1212334455
10:1122334455


*/
