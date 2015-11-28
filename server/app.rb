require "sinatra"
require "sinatra/reloader" if development?
require 'active_record'
require 'json'
#require 'omniauth-twitter'
#require 'twitter'

#mysql
ActiveRecord::Base.configurations = YAML.load_file('database.yml')
ActiveRecord::Base.establish_connection('development')

class Topic < ActiveRecord::Base
end

#Time out error
after do
  ActiveRecord::Base.connection.close
end

#########################################################################################

get '/' do
	"Hello World"
end


get '/home' do
	erb :home
end

get '/water/:id' do
	erb :water
end

get '/register' do
	erb :register
end

post '/register' do
	'register'
end

get '/login' do
	erb :login
end

post '/login' do
	'login'
end




