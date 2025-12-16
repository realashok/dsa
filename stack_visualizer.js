import React, { useState } from 'react';
import { Play, RotateCcw, Plus, Minus } from 'lucide-react';

const StackVisualizer = () => {
  const [stack, setStack] = useState([]);
  const [inputValue, setInputValue] = useState('');
  const [message, setMessage] = useState('');
  const [animating, setAnimating] = useState(null);

  const push = () => {
    const value = parseInt(inputValue);
    if (isNaN(value)) {
      setMessage('Please enter a valid number');
      return;
    }
    
    setAnimating('push');
    setTimeout(() => {
      setStack([value, ...stack]);
      setMessage(`Pushed ${value} onto stack`);
      setInputValue('');
      setAnimating(null);
    }, 300);
  };

  const pop = () => {
    if (stack.length === 0) {
      setMessage('Stack Underflow!');
      return;
    }
    
    setAnimating('pop');
    setTimeout(() => {
      const value = stack[0];
      setStack(stack.slice(1));
      setMessage(`Popped ${value} from stack`);
      setAnimating(null);
    }, 300);
  };

  const peek = () => {
    if (stack.length === 0) {
      setMessage('Stack is empty');
      return;
    }
    setMessage(`Top element: ${stack[0]}`);
  };

  const reset = () => {
    setStack([]);
    setMessage('Stack reset');
    setInputValue('');
  };

  const runDemo = () => {
    setStack([]);
    setMessage('Running demo...');
    
    setTimeout(() => {
      setStack([10]);
      setMessage('Pushed 10');
    }, 500);
    
    setTimeout(() => {
      setStack([20, 10]);
      setMessage('Pushed 20');
    }, 1500);
    
    setTimeout(() => {
      setStack([40, 20, 10]);
      setMessage('Pushed 40');
    }, 2500);
    
    setTimeout(() => {
      setStack([20, 10]);
      setMessage('Popped 40');
    }, 4000);
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 to-slate-800 p-8">
      <div className="max-w-4xl mx-auto">
        <h1 className="text-4xl font-bold text-white mb-2 text-center">Stack Visualizer</h1>
        <p className="text-slate-300 text-center mb-8">Linked List Implementation (LIFO)</p>
        
        <div className="grid md:grid-cols-2 gap-8">
          {/* Controls */}
          <div className="bg-slate-800 rounded-lg p-6 border border-slate-700">
            <h2 className="text-xl font-semibold text-white mb-4">Controls</h2>
            
            <div className="space-y-4">
              <div>
                <label className="block text-sm text-slate-300 mb-2">Value to Push</label>
                <input
                  type="number"
                  value={inputValue}
                  onChange={(e) => setInputValue(e.target.value)}
                  onKeyPress={(e) => e.key === 'Enter' && push()}
                  className="w-full bg-slate-700 text-white px-4 py-2 rounded border border-slate-600 focus:border-blue-500 focus:outline-none"
                  placeholder="Enter number"
                />
              </div>
              
              <div className="grid grid-cols-2 gap-3">
                <button
                  onClick={push}
                  className="flex items-center justify-center gap-2 bg-green-600 hover:bg-green-700 text-white px-4 py-2 rounded font-medium transition"
                >
                  <Plus size={18} /> Push
                </button>
                <button
                  onClick={pop}
                  className="flex items-center justify-center gap-2 bg-red-600 hover:bg-red-700 text-white px-4 py-2 rounded font-medium transition"
                >
                  <Minus size={18} /> Pop
                </button>
              </div>
              
              <button
                onClick={peek}
                className="w-full bg-blue-600 hover:bg-blue-700 text-white px-4 py-2 rounded font-medium transition"
              >
                Peek
              </button>
              
              <div className="grid grid-cols-2 gap-3">
                <button
                  onClick={runDemo}
                  className="flex items-center justify-center gap-2 bg-purple-600 hover:bg-purple-700 text-white px-4 py-2 rounded font-medium transition"
                >
                  <Play size={18} /> Demo
                </button>
                <button
                  onClick={reset}
                  className="flex items-center justify-center gap-2 bg-slate-600 hover:bg-slate-700 text-white px-4 py-2 rounded font-medium transition"
                >
                  <RotateCcw size={18} /> Reset
                </button>
              </div>
            </div>
            
            {message && (
              <div className="mt-4 p-3 bg-slate-700 rounded border border-slate-600 text-slate-200 text-sm">
                {message}
              </div>
            )}
            
            <div className="mt-6 p-4 bg-slate-900 rounded border border-slate-700">
              <div className="text-sm text-slate-300 space-y-1">
                <p><strong className="text-white">Size:</strong> {stack.length}</p>
                <p><strong className="text-white">Top:</strong> {stack.length > 0 ? stack[0] : 'NULL'}</p>
                <p><strong className="text-white">Empty:</strong> {stack.length === 0 ? 'Yes' : 'No'}</p>
              </div>
            </div>
          </div>
          
          {/* Visualization */}
          <div className="bg-slate-800 rounded-lg p-6 border border-slate-700">
            <h2 className="text-xl font-semibold text-white mb-4">Stack Structure</h2>
            
            <div className="flex flex-col items-center">
              <div className="text-sm text-slate-400 mb-2">HEAD (Top) ↓</div>
              
              {stack.length === 0 ? (
                <div className="text-slate-500 text-center py-12 border-2 border-dashed border-slate-700 rounded-lg w-full">
                  Stack is empty (NULL)
                </div>
              ) : (
                <div className="space-y-2 w-full">
                  {stack.map((value, index) => (
                    <div
                      key={index}
                      className={`transition-all duration-300 ${
                        animating === 'push' && index === 0 ? 'scale-110 opacity-0' : 
                        animating === 'pop' && index === 0 ? 'scale-90 opacity-50' : 
                        'scale-100 opacity-100'
                      }`}
                    >
                      <div className="bg-gradient-to-r from-blue-600 to-blue-500 rounded-lg p-4 border-2 border-blue-400 shadow-lg">
                        <div className="flex justify-between items-center">
                          <div>
                            <div className="text-xs text-blue-200 mb-1">Node {index}</div>
                            <div className="text-2xl font-bold text-white">{value}</div>
                          </div>
                          <div className="text-xs text-blue-200">
                            {index === 0 && <span className="bg-blue-400 text-blue-900 px-2 py-1 rounded font-semibold">TOP</span>}
                          </div>
                        </div>
                        <div className="mt-2 text-xs text-blue-200">
                          next: {index < stack.length - 1 ? `→ Node ${index + 1}` : 'NULL'}
                        </div>
                      </div>
                      {index < stack.length - 1 && (
                        <div className="flex justify-center">
                          <div className="w-1 h-4 bg-slate-600"></div>
                        </div>
                      )}
                    </div>
                  ))}
                </div>
              )}
              
              {stack.length > 0 && (
                <div className="text-sm text-slate-400 mt-2">↑ NULL</div>
              )}
            </div>
          </div>
        </div>
        
        <div className="mt-8 bg-slate-800 rounded-lg p-6 border border-slate-700">
          <h3 className="text-lg font-semibold text-white mb-3">How It Works</h3>
          <div className="grid md:grid-cols-3 gap-4 text-sm text-slate-300">
            <div>
              <strong className="text-green-400">Push:</strong> Adds a new node at the head of the linked list (top of stack). The new node's next pointer points to the previous head.
            </div>
            <div>
              <strong className="text-red-400">Pop:</strong> Removes the head node and returns its value. The head pointer moves to the next node.
            </div>
            <div>
              <strong className="text-blue-400">Peek:</strong> Returns the value at the head without removing it. Returns -1 if stack is empty.
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default StackVisualizer;