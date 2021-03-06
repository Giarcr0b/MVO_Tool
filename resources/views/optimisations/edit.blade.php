@extends('layouts.app')

@section('title')
    Edit Optimisation
@endsection

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-8 col-md-offset-2">
                <div class="panel panel-default">
                    <div class="panel-heading">Edit Optimisation</div>

                    <div class="panel-body">
                        <form class="form-horizontal" role="form" method="post" action="/optimisations/{{ $optimisation->id }}">
                            {{ method_field('PUT') }}

                            {{ csrf_field() }}
                            <input type="hidden" name="user_id" value="{{ Auth::user()->id }}">

                            <div class="form-group{{ $errors->has('name') ? ' has-error' : '' }}">
                                <label for="name" class="col-md-4 control-label">Optimisation Name</label>

                                <div class="col-md-6">
                                    <input id="name" type="text" class="form-control" name="name"
                                           value="{{ $optimisation->name }}" required autofocus>

                                    @if ($errors->has('name'))
                                        <span class="help-block">
                                        <strong>{{ $errors->first('name') }}</strong>
                                    </span>
                                    @endif
                                </div>
                            </div>

                            <div class="form-group{{ $errors->has('description') ? ' has-error' : '' }}">
                                <label for="description" class="col-md-4 control-label">Optimisation Description</label>

                                <div class="col-md-6">
                                    <input id="description" type="text" class="form-control" name="description"
                                           value="{{ $optimisation->description }}" required>

                                    @if ($errors->has('description'))
                                        <span class="help-block">
                                        <strong>{{ $errors->first('description') }}</strong>
                                    </span>
                                    @endif
                                </div>
                            </div>

                            <div class="form-group">
                                <div class="col-md-8 col-md-offset-4">
                                    <a class="btn btn-primary" href="/optimisations/{{ $optimisation->id }}">
                                        Cancel
                                    </a>
                                    <button type="submit" class="btn btn-primary">
                                        Update Optimisation
                                    </button>
                                </div>
                            </div>
                        </form>

                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection