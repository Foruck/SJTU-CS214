from math import log
import operator
def createDataset():
	dataSet=[['young','myope','no','reduced','no'],
		['young','myope','no','normal','soft'],
		['young','myope','yes','reduced','no'],
		['young','myope','yes','normal','hard'],
		['young','hyper','no','reduced','no'],
		['young','hyper','no','normal','soft'],
		['young','hyper','yes','reduced','no'],
		['young','hyper','yes','normal','hard'],
		['pre','myope','no','reduced','no'],
		['pre','myope','no','normal','soft'],
		['pre','myope','yes','reduced','no'],
		['pre','myope','yes','normal','hard'],
		['pre','hyper','no','reduced','no'],
		['pre','hyper','no','normal','soft'],
		['pre','hyper','yes','reduced','no'],
		['pre','hyper','yes','normal','no'],
		['presbyopic','myope','no','reduced','no'],
		['presbyopic','myope','no','normal','no'],
		['presbyopic','myope','yes','reduced','no'],
		['presbyopic','myope','yes','normal','hard'],
		['presbyopic','hyper','no','reduced','no'],
		['presbyopic','hyper','no','normal','soft'],
		['presbyopic','hyper','yes','reduced','no'],
		['presbyopic','hyper','yes','normal','no']]
	labels=['age','prescript','astigmatic','tear_rate']
	return dataSet,labels
def calcEnt(dataSet):
	num=len(dataSet)
	Counts={}
	for feat in dataSet:
		label=feat[-1]
		if label not in Counts.keys():
			Counts[label]=0
		Counts[label]+=1
	ans=0.0
	for key in Counts:
		p=float(Counts[key])/num
		ans-=p*log(p,2)
	return ans
def split(dataSet,axis,value):
	retDataSet=[]
	for feat in dataSet:
		if feat[axis]==value:
			reducedFeat=feat[:axis]
			reducedFeat.extend(feat[axis+1:])
			retDataSet.append(reducedFeat)
	return retDataSet
def chooseBest(dataSet):
	num=len(dataSet[0])-1
	base=calcEnt(dataSet)
	m=0.0
	k=-1
	for i in range(num):
		featlist=[example[i] for example in dataSet]
		v=set(featlist)
		ent=0
		for value in v:
			subds=split(dataSet,i,value)
			p=len(subds)/float(len(dataSet))
			ent+=p*calcEnt(subds)
		if (base-ent>m):
			m=base-ent
			k=i
	return k
def majorCnt(classList):
	classCount={}
	for v in classList:
		if v not in classCount.keys():
			classCount[v]=0
		classCount[v]+=1
	sortedClassCount=sorted(classCount.iteritems(),key=operator.imtemgetter(1),reverse=True)
	return sortedClassCount[0][0]
def createTree(dataSet,labels):
	classList=[example[-1] for example in dataSet]
	if classList.count(classList[0])==len(classList):
		return classList[0]
	if len(dataSet[0])==1:
		return majorCnt(classList)
	best=chooseBest(dataSet)
	print best
	bestlabel=labels[best]
	myTree={bestlabel:{}}
	del(labels[best])
	featValues=[example[best] for example in dataSet]
	uniqueVals=set(featValues)
	for value in uniqueVals:
		subLabels=labels[:]
		myTree[bestlabel][value]=createTree(split(dataSet,best,value),subLabels)
	return myTree
def classify(inputTree,featLabels,testVec):
	firstStr=inputTree.keys()[0]
	secondDict=inputTree[firstStr]
	featIndex=featLabels.index(firstStr)
	for key in secondDict.keys():
		if testVec[featIndex]==key:
			if type(secondDict[key]).__name__=='dict':
				classLabel=classify(secondDict[key],featLabels,testVec)
			else:
				classLabel=secondDict[key]
	return classLabel
