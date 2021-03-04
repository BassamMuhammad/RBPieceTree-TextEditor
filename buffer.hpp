#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <string>
#include <vector>

using namespace std;
class Buffer{
	private:
        string text;				//stores text
        vector<int> lineFeeds;		//stores offset of line-feed
		
	public:
		//constructor
        Buffer(string nText, vector<int> nLineFeeds);
		
		//getters
        string getText();
        vector<int> getLineFeeds();
};

#endif

