workers 1
preload_app!
threads 2, 4

path = '/opt/www/student_bazaar/shared'
bind "unix://#{path}/sockets/puma.socket"
state_path "#{path}/puma.state"
pidfile "#{path}/pids/puma.pid"


rackup      DefaultRackup
environment ENV['RACK_ENV'] || 'development'

on_worker_boot do
  ActiveSupport.on_load(:active_record) do
    ActiveRecord::Base.establish_connection
  end
end
