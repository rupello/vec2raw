env = Environment()
env.Append(CCFLAGS='-g')
env.ParseConfig( 'pkg-config --cflags --libs itpp' )
env.Program('vec2raw.cpp')
