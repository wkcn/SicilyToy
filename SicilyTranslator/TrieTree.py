freq = ['e','a','i','t','o','r','n','s','l','c','u','d','p','h','m','g','f','b','y','w','v','k','x','z','j','q']

class TrieNode:
	def __init__(self):
		self.value = 0
		self.children = []

class TrieTree:
	def __init__(self):
		self.root = TrieNode()
		self.ids = range(26)
		id = 0
		for c in freq:
			self.ids[ord(c) - ord('a')] = id
			id += 1
			
	def insert(self,word,content):
		node = self.root
		for c in word.lower():
			if not (c >= 'a' and c <= 'z'):
				continue
			id = self.ids[ord(c) - ord('a')]
			if id >= len(node.children):
				node.children += [TrieNode() for i in range(id - len(node.children) + 1)]
			node = node.children[id]
		node.value = content
		
	def find(self,word):
		node = self.root
		for c in word.lower():
			if not (c >= 'a' and c <= 'z'):
				continue
			id = self.ids[ord(c) - ord('a')]
			if id >= len(node.children):
				return ''
			node = node.children[id]
		return node.value
		
class SDict:
	def __init__(self):
		self.data = {}
	def insert(self,word,content):
		self.data[word] = content
	def find(self,word):
		return self.data.get(word,'')