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
	int index;
	int weight;
	int length;
	float ratio; //按照weight/length
};
/*************自定义比较函数，按照ratio从大到小排列***************/
class mycompare
{
	bool reverse;
public:
	mycompare(const bool & re = false)
	{reverse = re;}
	bool operator() (Job &a, Job &b) const
	{
		if(reverse) return (a.ratio > b.ratio);//实现从小到大的排列
		else {
			if(a.ratio == b.ratio) 
			{
				return (a.weight < b.weight); // 如果相等，则选择weight大的排在前
			} else {
				return (a.ratio < b.ratio); //从大到小
			}
		}
	}
};

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
			jobs[cnt].ratio =( (float)_wei) / _len;
			mypq.push(jobs[cnt]);
			cnt++;
		}	
	}

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
	priority_queue <Job, vector< Job > ,mycompare> mypq;
};

int main()
{
	JobShedule jobsh;
//	jobsh.get_data();
//	jobsh.write();
	jobsh.calc_time();
	cout << "total time:" << jobsh.time << endl;
	return 0;
}











