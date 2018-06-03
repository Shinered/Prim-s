#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;


class Job
{
public:
	int index;  //工作号
	int weight; //权重
	int length; //工作时长
	int we_le; //weight-length
};
/***********优先队列Job类自定义比较函数**********/
class mycompare
{
	bool reverse;
public:
	mycompare(const bool & re = false)
	{reverse = re;}
	bool operator() (Job &a, Job &b) const
	{
		if(reverse) return (a.we_le > b.we_le);//实现从小到大的排列
		else {
			if(a.we_le == b.we_le) 
			{
				return (a.weight < b.weight); // 如果相等，则选择weight大的排在前
			} else {
				return (a.we_le < b.we_le); //从大到小
			}
		}
	}
};
/*************工作安排*******************/
class JobShedule
{
public:
	JobShedule()
	{
		ifstream fin("t.txt");
		string line;
		stringstream stream;
		if(getline(fin,line))
		{
			stream.clear();
			stream << line;
			stream >> count;
		}
		int cnt = 0;
		while(getline(fin, line))
		{
			int _len, _wei;
			stream.clear();
			stream << line;
			stream >> _wei;
			stream >> _len;
			jobs[cnt].index = cnt + 1;
			jobs[cnt].length = _len;
			jobs[cnt].weight = _wei;
			jobs[cnt].we_le = _wei - _len;
			mypq.push(jobs[cnt]);
			cnt++;
		}	
	}


/*************计算总的带权重的工作时间**************/	
	void calc_time()
	{
		ofstream fout;
		fout.open("output.txt");
		while(!mypq.empty())				
		{
			Job tmp = mypq.top();
			mypq.pop();
			curLength += tmp.length;
			time += tmp.weight * curLength;
			fout << "tmp time:: " << time << endl;
		}
	}

public:
	int count;
	long long time = 0;
	int curLength = 0;
	Job jobs[12];
	//优先队列，按照工作的weight-length排列队列。
	priority_queue <Job, vector< Job > ,mycompare> mypq;
};

int main()
{
	JobShedule jobsh;
	jobsh.calc_time();
	cout << "total time:" << jobsh.time << endl;
	return 0;
}











